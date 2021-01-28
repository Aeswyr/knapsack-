#pragma once

#include "knapsack/sprite.h"
#include "knapsack/vector.h"

class Tileset {
private:
    Sprite* sprite;
    int tilesize;
public:
    Tileset() {};
    Tileset(std::string name, int tilesize);
    void render(float x, float y, Vector3 map);
    ~Tileset();
};

namespace tileset {
    Vector3 defaultmap(int** arr, int x, int y, int w, int h);
    Vector3 defaultmap(int* arr, int x, int y, int w, int h);
};