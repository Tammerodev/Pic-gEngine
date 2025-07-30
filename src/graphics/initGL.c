#include "graphicsGL.h"
#include <GL/gl.h>
#include <GL/glu.h>

void picg_gl_setClearColor(float r, float g, float b, float a) 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear the color buffer
    glClearColor(r, g, b, a);
}

void picg_gl_init3D(int winX, int winY)
{
    // View projection
    glMatrixMode(GL_PROJECTION);
    gluPerspective(100.f, (float) winX / (float)winY, 0.1f, 10000000.f);

    // Enable GL propeties
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
}

void picg_gl_setPerspective(int winX, int winY, float FOV, float zNear, float zFar) {
    glMatrixMode(GL_PROJECTION);
    gluPerspective(FOV, (float) winX / (float)winY, zNear, zFar);
}