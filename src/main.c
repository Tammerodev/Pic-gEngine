#include <stdio.h>

#include "GL/gl.h"
#include "GL/glu.h"

#include "window/window.h"
#include "graphics/graphicsGL.h"
#include "graphics/object/objects.h"
#include "graphics/lighting/lightSource.h"
#include "graphics/camera/camera.h"

int main(int argc, char** argv) 
{   
    picg_window_create(800, 800, "Test");
    picg_gl_init3D();
    picg_gl_setClearColor(0.5, 0.5, 1.0, 1.0);

    picg_mesh* teapot = picg_modelObj_create("dev/Models/teapot.obj");
    picg_mesh* cube = picg_modelObj_create("dev/Models/cube.obj");
    picg_mesh* cow = picg_modelObj_create("dev/Models/cow.obj");

    picg_camera* camera = picg_camera_create();

    cow->position.z = -15.0f;
    cube->position.x = 30.f;

    camera->position.z = -30.f;

    for(;;) {
        picg_gl_clear();
        picg_camera_push(camera);

        if(picg_keyboard_keydown("W"))
            camera->position.z += 0.1;

        if(picg_keyboard_keydown("A"))
            camera->position.x += 0.1;

        if(picg_keyboard_keydown("S"))
            camera->position.z -= 0.1;

        if(picg_keyboard_keydown("D"))
            camera->position.x -= 0.1;

        teapot->rotation.y += 1.5;

        cube->rotation.z -= 0.5;
        cube->rotation.y -= 0.5;
        cube->rotation.x -= 0.5;

        picg_mesh_render(teapot);
        picg_mesh_render(cube);
        picg_mesh_render(cow);
        picg_camera_push(camera);


        picg_window_display();
        picg_camera_pop(camera);
    }
    return 0;
}