#pragma once

/**
 * a base class which all Systems must extend. Systems are
 * instructions which operate on a subset of entities with a specific
 * set of components.
 */ 
class System {
public:
    virtual void run() = 0;
};