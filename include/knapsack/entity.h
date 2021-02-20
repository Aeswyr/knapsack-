#pragma once

#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#include <boost/dynamic_bitset.hpp>

#include "knapsack/internal/entity.h"

#include <knapsack/component.h>
#include <knapsack/renderer.h>

class Entity;

 /**
 * contains a number of functions related to operations on the list of all active entities
 */ 
namespace ecs {
    namespace entity {
        /**
         * creates and returns a new entity
         * 
         * returns      -   A reference to the entity created
         */ 
        Entity& create();

        /**
         * fetches an entity reference based on the provided entity
         * 
         * EntityID id  -   The id of the entity to fetch
         * returns      -   A reference to the entity corresponding to the
         *                  given ID or null if no entity is found
         */ 
        Entity& get(EntityID id);

        /**
         * removes an entity from the list of active entities
         * 
         * EntityID id    -   The id of the entity to remove
         */ 
        void del(EntityID id);

        /**
         * clears all existing entities
         */ 
        void clear();
    };
};


static EntityID id_source;

class Entity {
private:
    std::vector<unsigned short int> componentPos = std::vector<unsigned short int>(CID_MAX);
    boost::dynamic_bitset<> validcomponents = boost::dynamic_bitset<>(CID_MAX);
    std::vector<Renderer*> renderers;
public:
    const EntityID ID = ++id_source;
    Entity();

    ~Entity();
    
    /**
     * Attaches a renderer to this entity, which is drawn each frame during runtime.
     * When an entity is deleted, all renderers associated with it are freed.
     * 
     * Renderer* r   -   a pointer to the renderer to attach
     */ 
    void attach(Renderer* r);

    /** called internally by the engine, runs render logic for each renderer
     * attached to this entity. User does not need to call
     */ 
    void render();

    /** called internally by the engine, runs update logic for each renderer
     * attached to this entity after ALL system logic is executed. User does not need to call
     */ 
    void update();

    /**
     * allocates memory for a new component on this entity and returns a pointer to that space,
     * or if the component already exists on this entity, returns a pointer to the space that
     * it exists in.
     * 
     * typename T    -   the type of the new component
     */ 
    template <typename T> T& set() {
        if (validcomponents[INTERNAL_ONLY_COMPONENT::getCID<T>()])
            return Component<T>::componentList[componentPos[INTERNAL_ONLY_COMPONENT::getCID<T>()]];
        validcomponents[INTERNAL_ONLY_COMPONENT::getCID<T>()] = 1;
        componentPos[INTERNAL_ONLY_COMPONENT::getCID<T>()] = Component<T>::componentList.size();
        typename Component<T>::ComponentDataPair comppair;
        comppair.ownerID = ID;
        Component<T>::componentList.push_back(comppair);
        return Component<T>::componentList[componentPos[INTERNAL_ONLY_COMPONENT::getCID<T>()]];
    }

    /**
     * checks if this entity has a given component
     * 
     * typename T   -   the type of the component to check for
     * returns      -   true if this entity has a given component, and false otherwise
     */ 
    template <typename T> bool has() {
        return validcomponents[INTERNAL_ONLY_COMPONENT::getCID<T>()];
    }

    /**
     * checks if this entity has a given component
     * 
     * unsigned int T   -   the component id to check for
     * returns          -   true if this entity has a given component, and false otherwise
     */ 
    bool has(unsigned int i) {
        return validcomponents[i];
    }

    /**
     * gets a pointer to acomponent on an entity
     * 
     * typename T   -   the type of the component to get
     * returns      -   a pointer to the component or null if the entity does not have the given component
     */ 
    template <typename T> T& get() {
        if (validcomponents[INTERNAL_ONLY_COMPONENT::getCID<T>()]) {
            return Component<T>::componentList[componentPos[INTERNAL_ONLY_COMPONENT::getCID<T>()]];
        }
        return nullptr;
    }

    /**
     * removes a component from this entity
     * 
     * typenname T  -   the type of the component to remove
     */ 
    template <typename T> void del() {
        if (validcomponents[INTERNAL_ONLY_COMPONENT::getCID<T>()]) {
            validcomponents[INTERNAL_ONLY_COMPONENT::getCID<T>()] = 0;
            unsigned short int pos = componentPos[INTERNAL_ONLY_COMPONENT::getCID<T>()];
            std::swap(Component<T>::componentList[pos], Component<T>::componentList[Component<T>::componentList.size() - 1]);
            Component<T>::componentList.pop_back();
            if (Component<T>::componentList.size() > 0) {
                ecs::entity::get(Component<T>::componentList[pos].ownerID).componentPos[INTERNAL_ONLY_COMPONENT::getCID<T>()] = pos;
            }
        }
    }
};


