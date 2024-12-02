#include <stdio.h>

#include "GL/gl.h"
#include "GL/glu.h"

#include "window/window.h"
#include "graphics/graphicsGL.h"
#include "graphics/object/objects.h"
#include "graphics/lighting/lightSource.h"
#include "graphics/camera/camera.h"

#include "math/timer.h"
#include <math.h>

int main(int argc, char** argv) 
{   
    const int sizeX = 1500;
    const int sizeY = 900;


    picg_window_create(sizeX, sizeY, "Pic-g 3D engine");
    picg_gl_init3D(sizeX, sizeY);
    picg_gl_setClearColor(0.5, 0.5, 1.0, 1.0);

    const int N = 25000;
    picg_mesh* meshes[N];

    float x = 0.f;
    float z = 0.f;

    for(int i = 0; i < N; i++) {
        meshes[i] = picg_modelObj_create("dev/Models/cube.obj");
        meshes[i]->position.x = x * 10.f;

        x += 1.f;
        if(x > (int)sqrt(N)) {
            x = 0.f;
            z += 10.f;
        }

        meshes[i]->position.z = z;
    } 

    picg_camera* camera = picg_camera_create();

    camera->position.y = -30.f;
    camera->position.z = -400.f;

    picg_ha_timer timer = {};

    double dt = 0.0;

    char title[48];
    for(;;) {
        picg_ha_timer_reset(&timer);
        picg_ha_timer_start(&timer);

        picg_gl_clear();
        picg_camera_push(camera);

        picg_window_mouse_getPosition();


        if(picg_keyboard_keydown("h")) 
            camera->rotation.y -= 0.5;
        if(picg_keyboard_keydown("k")) 
            camera->rotation.y += 0.5;
        if(picg_keyboard_keydown("j")) 
            camera->rotation.x += 0.5;
        if(picg_keyboard_keydown("u")) 
            camera->rotation.x -= 0.5;

        double speed = 100.0 * dt;

        if(picg_keyboard_keydown("W"))
            camera->position.z += speed;

        if(picg_keyboard_keydown("A"))
            camera->position.x += speed;

        if(picg_keyboard_keydown("S"))
            camera->position.z -= speed;

        if(picg_keyboard_keydown("D"))
            camera->position.x -= speed;

        if(picg_keyboard_keydown("space"))
            camera->position.y -= speed;

        if(picg_keyboard_keydown("x"))
            camera->position.y += speed;

        for(int i = 0; i < N; ++i) {
            if(meshes[i])
                picg_mesh_render(meshes[i]);
        }

        picg_camera_push(camera);

        picg_window_display();
        picg_camera_pop(camera);

        dt = picg_ha_timer_gettime(&timer);

        sprintf(title, "Pic-g 3d engine, FPS: %f", 1.f / (float)picg_ha_timer_gettime(&timer));
        picg_window_setTitle(title);
    }
    return 0;
}