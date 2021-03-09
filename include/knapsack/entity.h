#pragma once

#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

#include "knapsack/internal/entity.h"

#include <knapsack/component.h>
#include <knapsack/renderer.h>
#include <knapsack/log.h>

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
    std::shared_ptr<void> validcomponents;
    std::vector<Renderer*> renderers;
    std::vector<unsigned short int> componentPos = std::vector<unsigned short int>(CID_MAX);

    bool bitsetGet(unsigned int CID);
    void bitsetSet(unsigned int CID, int val);
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
     * performs an & operation this entity's internal bitset to the mask bitset to check for overlap
     * 
     * returns      -   true if the mask bitset completely overlaps, and false otherwise
     */ 
    bool mask(void* mask);

    /**
     * performs an & operation this entity's internal bitset to the mask bitset to check equality
     * 
     * returns      -   true if the mask bitset equals the input value, and false otherwise
     */ 
    bool mask(void* mask, void* test);

    /**
     * allocates memory for a new component on this entity and returns a pointer to that space,
     * or if the component already exists on this entity, returns a pointer to the space that
     * it exists in.
     * 
     * typename T    -   the type of the new component
     */ 
    template <typename T> T& set() {
        if (bitsetGet(INTERNAL_ONLY_COMPONENT::getCID<T>()))
            return Component<T>::componentList.list[componentPos[INTERNAL_ONLY_COMPONENT::getCID<T>()]].component;
        bitsetSet(INTERNAL_ONLY_COMPONENT::getCID<T>(), 1);
        componentPos[INTERNAL_ONLY_COMPONENT::getCID<T>()] = Component<T>::componentList.list.size();
        ComponentDataPair<T> comppair;
        comppair.ownerID = ID;
        Component<T>::componentList.list.push_back(comppair);
        return Component<T>::componentList.list[componentPos[INTERNAL_ONLY_COMPONENT::getCID<T>()]].component;
    }

    /**
     * checks if this entity has a given component
     * 
     * typename T   -   the type of the component to check for
     * returns      -   true if this entity has a given component, and false otherwise
     */ 
    template <typename T> bool has() {
        return bitsetGet(INTERNAL_ONLY_COMPONENT::getCID<T>());
    }

    /**
     * checks if this entity has a given component
     * 
     * unsigned int T   -   the component id to check for
     * returns          -   true if this entity has a given component, and false otherwise
     */ 
    bool has(unsigned int i);

    /**
     * gets a pointer to acomponent on an entity
     * 
     * typename T   -   the type of the component to get
     * returns      -   a pointer to the component or NULL_ENTITY if the entity does not have the given component
     */ 
    template <typename T> T& get() {
        if (bitsetGet(INTERNAL_ONLY_COMPONENT::getCID<T>())) {
            return Component<T>::componentList.list[componentPos[INTERNAL_ONLY_COMPONENT::getCID<T>()]].component;
        }
        out::log << out::err << "Invalid get attempt, Entity " << ID.gen << "::" << ID.id << " does not have component " << typeid(T).name() << out::endl;
        exit(1);
    }

    /**
     * removes a component from this entity
     * 
     * typenname T  -   the type of the component to remove
     */ 
    template <typename T> void del() {
        if (bitsetGet(INTERNAL_ONLY_COMPONENT::getCID<T>())) {
            bitsetSet(INTERNAL_ONLY_COMPONENT::getCID<T>(), 0);
            unsigned short int pos = componentPos[INTERNAL_ONLY_COMPONENT::getCID<T>()];
            Component<T>::componentList.remove(pos);
        }
    }

    unsigned short int& compPos(unsigned int CID);
};


