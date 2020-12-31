#include "entity.h"
#include "camera.h"

Entity::Entity() {

}

void Entity::tick() {
    if (inactive)
        inactive--;
}


Entity::~Entity() {
    for (auto iterator = hitboxes.begin(); iterator != hitboxes.end(); iterator++)
        delete(iterator->second);
}

Hitbox* Entity::hitbox(std::string name) {
    if (hitboxes.find(name) != hitboxes.end())
        return hitboxes[name];
    return nullptr;
}

Hitbox* Entity::registerHitbox(std::string name) {
    hitboxes[name] = new Hitbox();
    return hitboxes[name];
}

Hitbox* Entity::registerHitbox(std::string name, int w, int h, Alignment* alignment) {
    Hitbox* hitbox = new Hitbox();
    hitbox->w = w;
    hitbox->h = h;
    hitbox->align = alignment;
    hitboxes[name] = hitbox;
    return hitbox;
}

void Entity::renderDevMode() {
    renderHitboxes(camera::x, camera::y);
}

void Entity::renderHitboxes(int xoff, int yoff) {
    for (auto iterator = hitboxes.begin(); iterator != hitboxes.end(); iterator++)
        hitbox::render(iterator->second, xoff, yoff);
}