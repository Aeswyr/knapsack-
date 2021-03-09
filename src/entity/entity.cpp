#include "knapsack/entity.h"

#include <boost/dynamic_bitset.hpp>

#include <knapsack/renderer.h>
#include <knapsack/internal/component.h>


Entity::Entity() {
    validcomponents = std::shared_ptr<void>(new boost::dynamic_bitset<>(CID_MAX, 0));
}

Entity::~Entity() {
    
    if (validcomponents.use_count() == 1) {
        //free all renderers
        for (Renderer* r : renderers) {
            delete(r);
        }
        renderers.clear();


        for (unsigned int i = 0; i < CID_MAX; i++) {
            if ((*(boost::dynamic_bitset<>*)validcomponents.get())[i]){
                removeComponentByID(i, componentPos[i]);
                (*(boost::dynamic_bitset<>*)validcomponents.get())[i] = 0;
            }
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

bool Entity::mask(void* mask) {
    return ((*(boost::dynamic_bitset<>*)validcomponents.get()) & (*(boost::dynamic_bitset<>*)mask)) == (*(boost::dynamic_bitset<>*)mask); 
}

bool Entity::mask(void* mask, void* test) {
    return ((*(boost::dynamic_bitset<>*)validcomponents.get()) & (*(boost::dynamic_bitset<>*)mask)) == (*(boost::dynamic_bitset<>*)test);
}

unsigned short int& Entity::compPos(unsigned int CID) {
    return componentPos[CID];
}

bool Entity::bitsetGet(unsigned int CID) {
    return (*(boost::dynamic_bitset<>*)validcomponents.get())[CID];
}

void Entity::bitsetSet(unsigned int CID, int val) {
    (*(boost::dynamic_bitset<>*)validcomponents.get())[CID] = val;
}

bool Entity::has(unsigned int i) {
    return (*(boost::dynamic_bitset<>*)validcomponents.get())[i];
}

