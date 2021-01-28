#pragma once

#include "knapsack/entity.h"

struct Renderer {

    virtual void update(Entity* e) {};

    virtual void render() = 0;

}