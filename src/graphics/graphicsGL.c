#include "graphicsGL.h"

void picg_gl_clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear the color buffer
}

void picg_gl_flush() {
    glFlush();  // Display
}