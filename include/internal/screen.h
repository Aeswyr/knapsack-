#pragma once
#include <GLFW/glfw3.h>

bool initWindow(int w, int h, const char* name);

void closeWindow();

GLFWwindow* getWindow();