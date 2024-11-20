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
    picg_window_create(800, 800, "Test");
    picg_gl_init3D();
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


    for(;;) {
        picg_ha_timer_reset(&timer);
        picg_ha_timer_start(&timer);

        picg_gl_clear();
        picg_camera_push(camera);

        double speed = 500.0 * dt;

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

        printf("FPS %f \n", 1.f / (float)picg_ha_timer_gettime(&timer));
    }
    return 0;
}