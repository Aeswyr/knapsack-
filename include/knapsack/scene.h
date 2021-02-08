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
};