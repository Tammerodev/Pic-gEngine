#include "lightSource.h"

void picg_addlight_diffuse(unsigned int lightNumber, GLfloat color[], GLfloat pos[]) 
{
    if(lightNumber > 7) {
        PICG_ERROR("Light numbers larger than 7 are not supported");
        return;
    }

    // 4 parameters; r,g,b,brightness

    GLfloat color_a[] = {color[0] * color[3], color[1] * color[3], color[2] * color[3]};

    glEnable(GL_LIGHT0 + lightNumber);

    glLightfv(GL_LIGHT0 + lightNumber, GL_DIFFUSE, color_a);
    glLightfv(GL_LIGHT0 + lightNumber, GL_POSITION, pos);
}

void picg_disablelight(unsigned int lightNumber)
{
    glDisable(GL_LIGHT0 + lightNumber);
}

void picg_addlight_ambient(GLfloat color[])
{
    // 4 parameters; r,g,b,brightness

    GLfloat color_a[] = {color[0] * color[3], color[1] * color[3], color[2] * color[3]};


    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, color_a);
}
