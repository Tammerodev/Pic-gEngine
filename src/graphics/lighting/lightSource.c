#include "lightSource.h"

void picg_addlight_diffuse(unsigned int lightNumber, GLfloat color[], GLfloat pos[]) 
{
    if(lightNumber>7) {
        printf("Error: lighsource.c, picg_addlight() failed: light numbers larger than 7 are not supported\n");
        return;
    }

    glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
}

void picg_addlight_ambient(GLfloat color[])
{
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, color);
}
