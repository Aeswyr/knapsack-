#pragma once

#include "knapsack/system.h"

/**
 * class representing a single gamestate and all behavior associated
 * with it
 */ 
class Scene {
public:
    
    /**
     * method called when using hnd::initscene(). Should contain
     * first time initialization behavior
     */ 
    virtual void init() {}

    /**
     * method called whenever this scene is switched into. this is
     * where all system registration should happen.
     */ 
    virtual void start() = 0; 

    /**
     * registers a target system with this scene, causing it to start
     * running. Systems execute in the order they are registered
     * 
     * System system    -   the system to register
     */ 
    void registerSystem(const System& system);
};