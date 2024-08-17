#include "lightSource.h"

void picg_addlight(unsigned int lightNumber, GLfloat color[], GLfloat pos[], GLenum lightType) {
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, color);
    
    /*glEnable(GL_LIGHT0 + lightNumber);
    glLightfv(GL_LIGHT0 + lightNumber, GL_AMBIENT, color);
    glLightfv(GL_LIGHT0 + lightNumber, GL_POSITION, pos);*/


}