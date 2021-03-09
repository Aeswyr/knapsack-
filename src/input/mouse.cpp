#include "knapsack/internal/eventpump.h"
#include "knapsack/input.h" 

#include <knapsack/globals.h>

static int X = 0, Y = 0;

void mouse::moveevent(GLFWwindow* window, double xpos, double ypos) {
    X = xpos;
    Y = ypos;
}

int mouse::x() {
    return X / GAMESCALE_X;
}

int mouse::y() {
    return Y / GAMESCALE_Y;
}

int mouse::x_adj() {
    return X;
}

int mouse::y_adj() {
    return Y;
}
