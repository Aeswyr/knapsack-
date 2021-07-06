#pragma once

#include <string>

struct Texture {
private:
	std::string path;
    int loaded;

    void lazyload();
    void unload();
    
public:
	int w, h, channels, colChannel, filterType;
    int frames, delta;
	unsigned int sheetTextureId = 0;
	float* clips;

	Texture(std::string path) : path(path) {
        loaded = 0;
    }

    Texture() : path(NULL) {}

    void update();
    void ping();
};