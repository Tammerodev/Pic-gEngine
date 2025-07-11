#pragma once
#include "graphicsGL.h"

/*
    Draws x-y-z crossed lines with diameter d
*/

void picg_graphics_debug_point_render(float x, float y, float z, float d) {
    glBegin(GL_LINES);

    glVertex3f(x - d, y, z);
    glVertex3f(x + d, y, z);

    glVertex3f(x, y, z - d);
    glVertex3f(x, y, z + d);

    glVertex3f(x, y - d, z);
    glVertex3f(x, y + d, z);

    glEnd();
}