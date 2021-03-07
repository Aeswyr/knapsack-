#include "knapsack/entity.h"

#include <knapsack/renderer.h>
#include <knapsack/internal/component.h>

Entity::Entity() {

}

Entity::~Entity() {
    //free all renderers
    for (Renderer* r : renderers) {
        delete(r);
    }
    //Release all components
    for (unsigned int i = 0; i < CID_MAX; i++) {
        if (validcomponents[i]){
            removeComponentByID(i, componentPos[i]);
            validcomponents[i] = 0;
        }
        
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

 bool Entity::mask(boost::dynamic_bitset<> mask) {
    return (validcomponents & mask) == mask;
 }