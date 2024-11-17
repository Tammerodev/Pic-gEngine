#include <stdio.h>

#include "GL/gl.h"

#include "window/window.h"
#include "graphics/graphicsGL.h"
#include "graphics/object/objects.h"
#include "graphics/lighting/lightSource.h"

int main(int argc, char** argv) 
{   
    picg_window_create(800, 800, "Test");
    picg_gl_init3D();
    picg_gl_setClearColor(0.5, 0.5, 1.0, 1.0);

    picg_mesh* teapot = picg_modelObj_create("dev/Models/teapot.obj");
    picg_mesh* rects = picg_modelObj_create("dev/Models/cow.obj");
    

    GLfloat pos[4];
    pos[0] = 1.0f;
    pos[1] = 0.0f;
    pos[2] = 0.0f;
    pos[3] = 0.0f;

    GLfloat col[4];
    col[0] = 1.f;
    col[1] = 1.3f;
    col[2] = 1.2f;
    col[3] = 1.0f;

    picg_addlight(0, col, pos, GL_LIGHT_MODEL_AMBIENT);


    for(;;) {
        picg_gl_clear();
        picg_mesh_render(teapot);
        picg_mesh_render(rects);


        teapot->rotation.y += 0.5;
        teapot->position.z += 0.01;
        rects->position.z -= 0.1;
        rects->rotation.z -= 0.5;
        rects->rotation.y -= 0.5;
        rects->rotation.x -= 0.5;

        picg_window_swapbuffers();
        picg_gl_flush();
    }
    return 0;
}