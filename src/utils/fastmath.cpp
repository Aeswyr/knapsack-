#include "knapsack/fastmath.h"

#include <cmath>

float cos(float dx, float dy) {
    return dx / sqrt(dx * dx + dy * dy);
}

float sin(float dx, float dy) {
    return dy / sqrt(dx * dx + dy * dy);
}

float tan(float dx, float dy) {
    return ((float)dy)/dx;
}

int angle(float dx, float dy) {
    return (int)((atan2(dy, dx)) * 180 / PI + 360) % 360;
}