#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#undef GLFW_INCLUDE_NONE

bool initWindow(int w, int h, const char* name);

void closeWindow();

GLFWwindow* getWindow();