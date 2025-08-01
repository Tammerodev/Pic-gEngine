#pragma once
#include "graphicsGL.h"

/*
    Draws x-y-z crossed lines with diameter d
*/

void picg_graphics_debug_point_render(float x, float y, float z, float d);
void picg_graphics_debug_ray_render(float x, float y, float z, float x2, float y2, float z2);