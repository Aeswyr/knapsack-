#pragma once

#include "knapsack/vector.h"

/**
 * Contains data representing position and orientation
 */
struct Alignment
{
public:
	Vector3 pos;
	Vector2 center;
	double theta;
};