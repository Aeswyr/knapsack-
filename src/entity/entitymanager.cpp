#include "knapsack/entity.h"
#include "knapsack/filter.h"

#include <unordered_map>
#include <vector>
#include <algorithm>

#include <knapsack/internal/entitymanager.h>
#include <knapsack/internal/entity.h>

#include <knapsack/globals.h>

struct EIDHash {
    size_t operator()(const EntityID& e) const { 
        return e.id; 
    } 
};

static std::unordered_map<EntityID, Entity, EIDHash> all_entity;
static std::vector<EntityID> to_remove;

void entities::update() {
    for (std::pair<EntityID, Entity> e : all_entity)
        e.second.update();
}

void entities::render() {
    for (std::pair<EntityID, Entity> e : all_entity)
        e.second.render();
}

Entity& ecs::entity::get(EntityID id) {
    return all_entity[id];
}

void ecs::entity::del(EntityID id) {
    all_entity.erase(id);
}

void ecs::entity::clear() {
    all_entity.clear();
}

Entity& ecs::entity::create() {
    Entity e;
    all_entity.emplace(e.ID, e);
    return all_entity[e.ID];
}

std::vector<EntityID> ecs::Filter::query() {
    std::vector<EntityID> q;
    for (std::pair<EntityID, Entity> e : all_entity) {
        bool has = true;
        for (unsigned int i : inc)
            if (!e.second.has(i))
                has = false;
        for (unsigned int i : exc)
            if (e.second.has(i))
                has = false;
        if (has)
            q.push_back(e.first);
    }
    return q;
}