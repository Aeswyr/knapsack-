#pragma once

#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>

#include <boost/dynamic_bitset.hpp>

#include "knapsack/hitbox.h"
#include "internal/entity.h"

static unsigned int id_source = 0;

class Entity {
private:
    std::vector<unsigned short int> componentPos = std::vector<unsigned short int>(CID_MAX);
    boost::dynamic_bitset<> validcomponents = boost::dynamic_bitset<>(CID_MAX);
protected:
    unsigned int id = ++id_source;

public:
    Entity();

    virtual ~Entity() = 0;
    
    /**
     * allocates memory for a new component on this entity and returns a pointer to that space,
     * or if the component already exists on this entity, returns a pointer to the space that
     * it exists in.
     * 
     * typename T    -   the type of the new component
     */ 
    template <typename T> T* set() {
        return nullptr; //TODO
    }

    /**
     * checks if this entity has a given component
     * 
     * typename T   -   the type of the component to check for
     * returns      -   true if this entity has a given component, and false otherwise
     */ 
    template <typename T> bool has() {
        return false; //TODO
    }

    /**
     * gets a pointer to acomponent on an entity
     * 
     * typename T   -   the type of the component to get
     * returns      -   a pointer to the component or null if the entity does not have the given component
     */ 
    template <typename T> T* get() {
        return nullptr; //TODO
    }

    /**
     * removes a component from this entity
     * 
     * typenname T  -   the type of the component to remove
     */ 
    template <typename T> void del() {
        return; //TODO
    }
};

 /**
 * contains a number of functions related to operations on the list of all active entities
 */ 
namespace entities {
    /**
     * gets a list of all active entities
     * 
     * returns  -   a pointer to the vector containing all entities
     */ 
    std::vector<Entity*>* all();

    /**
     * adds a new entity to the list of active entities
     * 
     * Entity* e    -   a pointer to the new entity to add
     */ 
    void add(Entity* e);

    /**
     * removes an entity from the list of active entities
     * 
     * Entity* e    -   a pointer to the new entity to remove
     */ 
    void remove(Entity* e);

    /**
     * clears the list of active entities completely
     */ 
    void clear();
};


