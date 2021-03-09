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

namespace ecs {
    namespace system {
        /**
         * registers a target system with this scene, causing it to start
         * running. Systems execute in the order they are registered
         * 
         * System system    -   the system to register
         */ 
        void add(System* system);

        /**
         * deregiesters all currently active systems
         */ 
        void clear();

        /**
         * deregiesters and FREES MEMORY for all currently active systems via their delete methods
         */ 
        void free();

    };
};