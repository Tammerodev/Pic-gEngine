#include "lightSource.h"

void picg_addlight(unsigned int lightNumber, GLfloat color[], GLfloat pos[], GLenum lightType) {
    if(lightNumber>7) {
        printf("Error: lighsource.c, picg_addlight() failed: light numbers larger than 7 are not supported\n");
        return;
    }

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0 + lightNumber);
    
    // Only diffuse (and optionally specular)
    glLightfv(GL_LIGHT0 + lightNumber, GL_DIFFUSE, color);
    glLightfv(GL_LIGHT0 + lightNumber, GL_SPECULAR, color); // Optional for shiny effects
}