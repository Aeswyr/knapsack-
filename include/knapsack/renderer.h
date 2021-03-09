#pragma once

#include <knapsack/entity.h>
class Entity;

struct Renderer {

    virtual void update(Entity* e) {};

    virtual void render() = 0;

};