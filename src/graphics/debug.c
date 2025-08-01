#include "debug.h"

void picg_graphics_debug_point_render(float x, float y, float z, float d)
{
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);

    glVertex3f(x - d, y, z);
    glVertex3f(x + d, y, z);

    glVertex3f(x, y, z - d);
    glVertex3f(x, y, z + d);

    glVertex3f(x, y - d, z);
    glVertex3f(x, y + d, z);

    glEnd();
    glEnable(GL_LIGHTING);
}

void picg_graphics_debug_ray_render(float x, float y, float z, float x2, float y2, float z2)
{
    glDisable(GL_LIGHTING);
    glColor3f(1.f, .0, .0);
    glBegin(GL_LINES);

    glVertex3f(x, y, z);
    glVertex3f(x2, y2, z2);

    glEnd();
    glEnable(GL_LIGHTING);
}