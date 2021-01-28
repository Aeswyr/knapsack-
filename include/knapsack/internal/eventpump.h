#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#undef GLFW_INCLUDE_NONE

namespace key {
    void update();
    
    void keyevent(GLFWwindow* window, int key, int scancode, int action, int mods);
    
    void init();
}

namespace mouse {
    void moveevent(GLFWwindow* window, double xpos, double ypos); 

    void keyevent(GLFWwindow* window, int button, int action, int mods);
}

namespace gamepad {

    //TODO redo
    
}