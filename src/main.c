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
    picg_gl_setClearColor(0.2, 0.1, 0.3, 1.0);

    GLfloat pos[4];
    pos[0] = 0.0f;
    pos[1] = 0.0f;
    pos[2] = .0f;
    pos[3] = 0.0f;

    GLfloat col[4];
    col[0] = 5.f;
    col[1] = 0.3f;
    col[2] = 0.2f;
    col[3] = 1.4f;

    picg_addlight(0, col, pos, GL_LIGHT_MODEL_AMBIENT);

    picg_mesh* cube = picg_cube_create();  
    picg_mesh* obj = picg_modelObj_create();
    

    //cube->position.z = -1.f;

    for(;;) {
        picg_gl_clear();
        //picg_mesh_render(cube);
        picg_mesh_render(obj);

        if(picg_keyboard_keydown("w")) obj->position.z += 0.005f;
        if(picg_keyboard_keydown("a")) obj->position.x += 0.005f;
        if(picg_keyboard_keydown("s")) obj->position.z -= 0.005f;
        if(picg_keyboard_keydown("d")) obj->position.x -= 0.005f;
        if(picg_keyboard_keydown("space")) obj->position.y += 0.005f;
        if(picg_keyboard_keydown("x")) obj->position.y -= 0.005f;
        


        picg_gl_flush();
    }
    return 0;
}