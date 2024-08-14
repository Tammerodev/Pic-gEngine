#include "graphicsGL.h"
#include "GL/gl.h"
#include "GL/glu.h"

void picg_gl_setClearColor(float r, float g, float b, float a) 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear the color buffer
    glClearColor(r, g, b, a);
}

void picg_gl_init3D()
{
    // View projection
    glMatrixMode(GL_PROJECTION);
    gluPerspective(90.f, 1.f, 0.1f, 1000.f);

    // Positions
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0F, 0.0F, -2.0F);

    // Enable GL propeties
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
}
