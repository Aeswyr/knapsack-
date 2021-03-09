#include "knapsack/handler.h"
#include "knapsack/scene.h"

#include <vector>
#include <string>
#include <unordered_map>

#include <knapsack/internal/handler.h>
#include <knapsack/internal/audio.h>
#include <knapsack/internal/eventpump.h>
#include <knapsack/internal/camera.h>
#include <knapsack/internal/entitymanager.h>
#include <knapsack/internal/particle.h>
#include <knapsack/internal/globals.h>

#include <knapsack/globals.h>
#include <knapsack/sprite.h>
#include <knapsack/text.h>

static Scene* activeScene = nullptr;

static std::vector<Sound*> engine_sounds;
static std::vector<Sound*> scene_sounds;

static std::unordered_map<std::string, AudioSource*>* audio_sources = new std::unordered_map<std::string, AudioSource*>();
static Text fpsdisplay("N/A", 16, {1, 1, 1, 1}), upsdisplay("N/A", 16, {1, 1, 1, 1}), msdisplay("N/A", 16, {1, 1, 1, 1});

void hnd::render() {
    particle::render();
    entities::render();
    if (ENGINE_DEV_MODE) {
        //dev mode render
    }
}

std::vector<System*> systems;
void hnd::update() {
    particle::update();
    camera::update();
    key::update();
    //gamepad::update();

    
    for(auto& sys : systems)
        sys->run();

    entities::update();

    if (ENGINE_DEV_MODE) {
        //dev mode update
    }
}

void hnd::setScene(Scene* scene) {
    scene->start();
    activeScene = scene;
}

void hnd::initScene(Scene* scene) {
    scene->init();
    scene->start();
    activeScene = scene;
}

void hnd_sfx::addSound(Sound* sound, AudioContext ctx) {
    switch (ctx)
    {
    case ADUIOCTX_engine:
        engine_sounds.push_back(sound);
        break;
    case ADUIOCTX_scene:
        scene_sounds.push_back(sound);
        break;
    }
}

AudioSource* engine::getAudioSource(std::string name) {
    AudioSource* source;
    if (audio_sources->find(name) == audio_sources->end()) {
        source = new AudioSource();
        (*audio_sources)[name] = source;
    } else {
        source = (*audio_sources)[name];
    }
    return source;
}

void ecs::system::add(System* system) {
    systems.push_back(system);
}

void ecs::system::free() {
    for(auto& sys : systems)
        delete(sys);
    systems.clear();
}

void ecs::system::clear() {
    systems.clear();
}
