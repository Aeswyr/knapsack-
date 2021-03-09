#include "knapsack/filter.h"

#include <memory>

#include <boost/dynamic_bitset.hpp>

#include <knapsack/internal/entity.h>


ecs::Filter ecs::filter() {
    Filter filter;
    return filter;
}

void ecs::Filter::reset() {
    (*(boost::dynamic_bitset<>*)inc.get()).reset();
    (*(boost::dynamic_bitset<>*)exc.get()).reset();
}

ecs::Filter::Filter() {
    inc = std::shared_ptr<void>(new boost::dynamic_bitset<>(CID_MAX, 0));
    exc = std::shared_ptr<void>(new boost::dynamic_bitset<>(CID_MAX, 0));
}

void ecs::Filter::setInc(unsigned int CID) {
    (*(boost::dynamic_bitset<>*)inc.get())[CID] = 1;
}

void ecs::Filter::setExc(unsigned int CID) {
    (*(boost::dynamic_bitset<>*)exc.get())[CID] = 1;
}