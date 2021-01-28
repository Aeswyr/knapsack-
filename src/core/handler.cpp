#include "knapsack/handler.h"

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

#include "knapsack/globals.h"
#include "knapsack/sprite.h"
#include "knapsack/text.h"

static Scene* activeScene = nullptr;

static std::vector<Sound*> engine_sounds;
static std::vector<Sound*> scene_sounds;

static std::unordered_map<std::string, AudioSource*>* audio_sources = new std::unordered_map<std::string, AudioSource*>();
static Text fpsdisplay("N/A", 16, {1, 1, 1, 1}), upsdisplay("N/A", 16, {1, 1, 1, 1}), msdisplay("N/A", 16, {1, 1, 1, 1});

void hnd::render() {
    particle::render();
    entities::render();
    if (ENGINE_DEV_MODE) {
        fpsdisplay.render(0, 172, ENGINE_Z);
        upsdisplay.render(0, 190, ENGINE_Z);
        msdisplay.render(0, 208, ENGINE_Z);
    }
}

void hnd::update() {
    particle::update();
    entities::update();
    camera::update();
    key::update();
    //gamepad::update();

    if (ENGINE_DEV_MODE) {
        std::string text = "FPS: ";
        text.append(std::to_string(ENGINE_FPS));
        fpsdisplay.update(text);
        text = "UPS: ";
        text.append(std::to_string(ENGINE_UPS));
        upsdisplay.update(text);
        text = "Tick(ms): ";
        text.append(std::to_string(ENGINE_MS));
        msdisplay.update(text);
    }
}

void hnd::setScene(Scene* scene) {
    activeScene = scene;
}

void hnd::initScene(Scene* scene) {
    scene->init();
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