#include <stdio.h>

#include "GL/gl.h"

#include "window/window.h"
#include "graphics/graphicsGL.h"
#include "graphics/object/objects.h"

int main(int argc, char** argv) 
{   
    picg_window_create(800, 800, "Test");
    picg_gl_init3D();
    picg_gl_setClearColor(0.2, 0.1, 0.3, 1.0);

    struct picg_mesh* cube = picg_cube_create();  

    for(;;) {
        glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer

        picg_mesh_render(cube);

        picg_event_handle();

        glFlush();  // Render now
    }

    printf("Hello world!");
    return 0;
}