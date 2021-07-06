#include "knapsack/entity.h"
#include "knapsack/filter.h"

#include <unordered_map>
#include <vector>
#include <algorithm>

#include <boost/dynamic_bitset.hpp>

#include <knapsack/internal/entitymanager.h>
#include <knapsack/internal/entity.h>

#include <knapsack/globals.h>

struct EIDHash {
    size_t operator()(const EntityID& e) const { 
        return e.id; 
    } 
};

static std::unordered_map<EntityID, Entity, EIDHash> all_entity;

void entities::update() {
    for (auto& e : all_entity)
        e.second.update();
}

void entities::render() {
    for (auto& e : all_entity)
        e.second.render();
}

Entity& ecs::entity::get(EntityID id) {
    return all_entity.at(id);
}

void ecs::entity::del(EntityID id) {
    all_entity.erase(id);
}

void ecs::entity::clear() {
    all_entity.clear();
}

Entity& ecs::entity::create() {
    Entity& e = *(new Entity);
    EntityID id = e.ID;
    all_entity.emplace(id, e);
    return all_entity[id];
}

std::vector<EntityID> ecs::Filter::query() {
    static boost::dynamic_bitset<> zero {CID_MAX, 0};
    std::vector<EntityID> q;
    for (auto& e : all_entity) {
        if (e.second.mask(exc.get(), &zero) && e.second.mask(inc.get()))
            q.push_back(e.first);
    }
    return q;
}