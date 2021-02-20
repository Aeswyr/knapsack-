#include "knapsack/entity.h"

#include <knapsack/renderer.h>

Entity::Entity() {

}

Entity::~Entity() {
    for (Renderer* r : renderers) {
        delete(r);
    }
}

 void Entity::attach(Renderer* r) {
     renderers.push_back(r);
 }

 void Entity::update() {
    for (Renderer* r : renderers) {
        r->update(this);
    }
 }

 void Entity::render() {
    for (Renderer* r : renderers) {
        r->render();
    }
 }