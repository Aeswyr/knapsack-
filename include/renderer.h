#include "entity.h"

struct Renderer {

    virtual void update(Entity* e) {};

    virtual void render() = 0;

}