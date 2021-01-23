#pragma once
#include "vec.h"

/**
 * struct representing a single connected gamepad/controller
 */
struct Gamepad;

/**
 * contains functions for interfacing with mouse inputs
 */ 
namespace mouse {
    /**
     * gets the x position of the mouse relative to the screen (not the camera)
     * 
     * returns  -   the x position of the mouse
     */ 
    int x();

    /**
     * gets the y position of the mouse relative to the screen (not the camera)
     * 
     * returns  -   the y position of the mouse
     */ 
    int y();

    /**
     * gets the real x position of the mouse relative to the screen (not the camera)
     *
     * 
     * returns  -   the x position of the mouse
     */ 
    int x_adj();

    /**
     * gets the real y position of the mouse relative to the screen (not the camera)
     *
     * 
     * returns  -   the y position of the mouse
     */ 
    int y_adj();

    /**
     * checks whether the specified mouse button is currently down
     * 
     * int code     -   GLFW_MOUSE_BUTTON representing the mouse button to check
     * returns      -   true if the mouse button is down, false otherwise
     */ 
    bool down(int code);

    /**
     * checks whether the specified mouse button was pressed this frame (transitioned from up to down)
     * 
     * int code     -   GLFW_MOUSE_BUTTON representing the mouse button to check
     * returns      -   true if the mouse button was pressed this frame, false otherwise
     */ 
    bool press(int code);

    /**
     * checks whether the specified mouse button was released this frame (transitioned from down to up)
     *
     * int code     -   GLFW_MOUSE_BUTTON representing the mouse button to check
     * returns      -   true if the mouse button was released this frame, false otherwise
     */ 
    bool release(int code);
}

/**
 * contains functions for interfacing with keyboard inputs
 */ 
namespace key {
    
    /**
     * checks whether the specified key is currently down
     * 
     * int code     -   GLFW_KEY representing the key to check
     * returns      -   true if the key is down, false otherwise
     */ 
    bool down(int code);

    /**
     * checks whether the specified key was pressed this frame (transitioned from up to down)
     * 
     * int code     -   GLFW_KEY representing the key to check
     * returns      -   true if the key was pressed this frame, false otherwise
     */ 
    bool press(int code);

    
    /**
     * checks whether the specified key was released this frame (transitioned from down to up)
     *
     * int code     -   GLFW_KEY representing the key to check
     * returns      -   true if the key was released this frame, false otherwise
     */ 
    bool release(int code);

    /**
     * remaps a key location, when the specified physical key is pressed, the game will treat
     * it as though the virtual key was pressed.
     * 
     * int phys     -   GLFW_KEY or GLFW_MOUSE_BUTTON of the physical key that is pressed
     * int vir      -   GLFW_KEY or GLFW_MOUSE_BUTTON of the key that the engine should read as
     *                  pressed when the physical key is pressed
     */ 
    void remap(int phys, int vir);

}

/**
 * contains functions for interfacing with gamepad/controller inputs
 */ 
namespace controller {

    //TODO redo

}