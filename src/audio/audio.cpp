#include <knapsack/internal/audio.h>

#include <string>
#include <unordered_map>

#include <knapsack/internal/import.h>
#include <knapsack/internal/resource.h>

#include "knapsack/handler.h"
#include "knapsack/log.h"


static std::unordered_map<std::string, Mix*> soundMap;

Mix* getMix(std::string name) {
    if (soundMap.find(name) == soundMap.end()) {
        out::log << out::err << name << " is not present in the sound map" << out::endl;
        exit(1);
    }
    Mix* ptr = soundMap[name];
    return ptr;
}

void imp::importAudio(std::string path) {
    imp::SoundData data = imp::parseSound(path);

    out::log << "\tcollecting data" << out::endl;
    
    std::string name = data.name;
    
    if (data.isMus) {
        Mus* sound = new Mus(data.path);
        soundMap[name] = sound;
        out::log << "\tmapping music at " << name << out::endl;
    } else {
        Sfx* sound = new Sfx(data.path);
        soundMap[name] = sound;
        out::log << "\tmapping sound at " << name << out::endl;
    }

    
}

void Mus::lazyload() {
    //data = Mix_LoadMUS(path.c_str());
    out::log << "lazyloaded music at " << path << out::endl;
}

void Mus::unload() {
    //Mix_FreeMusic(data);
    out::log << "unloaded music at " << path << out::endl;
}

int Mus::play(int loops) {
    ping();
    //Mix_PlayMusic(data, loops);
    return -2;
}

void Sfx::lazyload() {
    //data = Mix_LoadWAV(path.c_str());
    out::log << "lazyloaded sound at " << path << out::endl;
}

void Sfx::unload() {
    //Mix_FreeChunk(data);
    out::log << "unloaded sound at " << path << out::endl;
}

int Sfx::play(int loops) {
    ping();
    return 0;//Mix_PlayChannel(-1, data, loops);
}

void Mix::update() {
	if(*loaded) {
		(*loaded)--;
		if (!(*loaded))
			unload();
	}
}

void Mix::ping() {
    if (!(*loaded)) {
		lazyload();
	}
	*loaded = 60;
}

Sound* AudioSource::play(std::string name) {
   
    Sound* sound = new Sound(name);
    sound->play(0);
    sound->setVolume(volume);
    hnd_sfx::addSound(sound, ADUIOCTX_engine);
    return sound;
}

Sound* AudioSource::play(std::string name, AudioContext ctx) {
        Sound* sound = new Sound(name);
    sound->play(0);
    sound->setVolume(volume);
    hnd_sfx::addSound(sound, ctx);
    return sound;
}

Sound* AudioSource::loop(std::string name, int loops) {
    Sound* sound = new Sound(name);
    sound->play(loops);
    sound->setVolume(volume);
    hnd_sfx::addSound(sound, ADUIOCTX_engine);
    return sound;
}

Sound* AudioSource::loop(std::string name, int loops, AudioContext ctx) {
    Sound* sound = new Sound(name);
    sound->play(loops);
    sound->setVolume(volume);
    hnd_sfx::addSound(sound, ctx);
    return sound;
}

void sfx::clean() {
	for (auto iterator = soundMap.begin(); iterator != soundMap.end(); iterator++) {
		iterator->second->update();
	}
}

Sound::Sound(std::string name) : sound(getMix(name)) {}

void Sound::play(int loops) {
    channel = sound->play(loops);
}

int Sound::setVolume(int vol) {
    if (channel == -2)
        return 0; //Mix_VolumeMusic(vol);
    else
        return 0; //Mix_Volume(channel, vol);
}

void Sound::stop() {
    if (channel == -2)
        ; //Mix_HaltMusic();
    else
        ; //Mix_HaltChannel(channel);
}

void sfx::init() {
    int audio_rate = 44100;
    //Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
    int audio_channels = 8;
    int audio_buffers = 4096;

    /*
    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) < 0) {
        flog::out << flog::err << "Unable to open audio!\n" << flog::endl;
        exit(1);
    }

    if(Mix_Init(MIX_INIT_MOD) != MIX_INIT_MOD)
        flog::out << flog::err << "error initializing sdl mixer" << flog::endl;
    */
}
