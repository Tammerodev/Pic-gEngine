#include <stdio.h>

#include "GL/gl.h"
#include "GL/glu.h"

#include "window/window.h"
#include "graphics/graphicsGL.h"
#include "graphics/object/objects.h"
#include "graphics/lighting/lightSource.h"
#include "graphics/camera/camera.h"

#include "physics/physicsComponent.h"


#include "math/timer.h"
#include "math/transforms.h"

#include <math.h>



int main(int argc, char** argv) 
{   
    const int sizeX = 1500;
    const int sizeY = 900;

    // Create & init graphics 
    picg_window_create(sizeX, sizeY, "Pic-g 3D engine", 0);
    picg_gl_init3D(sizeX, sizeY);
    picg_gl_setClearColor(0.01, 0.01, 0.02, 1.0);

    // Teapot
    picg_mesh* obj = picg_modelObj_create("dev/Models/teapot.obj"); 

    picg_vec3F rotation = {0.f, 0.f, 0.f};

    float x = 0.f;
    float z = 0.f;
    // Make a grid of cubes (size=N)

    const int N = 6200;
    picg_mesh* meshes[N];
    picg_physics_physicsComponent* physic[N];

    for(int i = 0; i < N; i++) {
        meshes[i] = picg_modelObj_create("dev/Models/cube.obj");
        meshes[i]->position.x = x * 5.f;

        x += 1.f;
        if(x > (int)sqrt(N)) {
            x = 0.f;
            z += 5.f;
        }

        meshes[i]->position.z = z;
        meshes[i]->position.y += sin(i / (float)1000.f * 1.f) * 1.f;
        meshes[i]->position.y += sin(x / 1.f) * 0.5f;

        // physics
        physic[i] = picg_physics_physicsComponent_create();
        picg_physics_physicsComponent_calculateAABB(&physic[i]->aabb, meshes[i]);

    } 

    // Create the camera
    picg_camera* camera = picg_camera_create();
    camera->position.y = -30.f;
    camera->position.z = -400.f;

    // Delta time
    picg_ha_timer timer = {};
    double dt = 0.0;

    char title[48];

    // Mouse movement stuff
    int persist_pos_x = 0;
    int persist_pos_y = 0;

    GLfloat color[] = {441.f, 0.0f, 0.1f, 20.6f};
    GLfloat pos[] = {0.f, 0.f, 0.f};

        // Basic lightting
        // picg_addlight(0, color, pos, GL_DIFFUSE);

    for(;;) {
        picg_ha_timer_reset(&timer);
        picg_ha_timer_start(&timer);

        picg_gl_clear();

        picg_window_mouse_getPosition();

        picg_camera_apply(camera);

        picg_vec2I mouse = picg_window_mouse_getPosition();
        picg_vec2I windowPos = picg_window_getPosition(); 
        picg_vec2I windowSize = picg_window_getSize();
        mouse.x -= (windowPos.x + windowSize.x / 2);
        mouse.y -= (windowPos.y + windowSize.y / 2);

        // TODO: uncomment
        /*if(mouse.x < -windowSize.x / 2) {
            picg_vec2I setPos = {windowPos.x + picg_window_mouse_getPosition().x + windowSize.x, picg_window_mouse_getPosition().y};
            picg_window_mouse_setPosition(setPos);
        }
        printf("mouse x %i y %i\n", mouse.x, mouse.y);*/

        if(picg_keyboard_keydown("o")) {

            camera->rotation.y = persist_pos_x + mouse.x / 5.f;
            camera->rotation.x = persist_pos_y + mouse.y / 5.f;
        }

        double rotation_speed = 1.7f * (dt + .1f);
        float dampening = 1.1f;

        if(picg_keyboard_keydown("h")) 
            rotation.y -= rotation_speed;
        if(picg_keyboard_keydown("k")) 
            rotation.y += rotation_speed;
        if(picg_keyboard_keydown("j")) 
            rotation.x += rotation_speed;
        if(picg_keyboard_keydown("u")) 
            rotation.x -= rotation_speed;

        rotation.x /= dampening;
        rotation.y /= dampening;
        rotation.z /= dampening;


        camera->rotation.x += rotation.x;
        camera->rotation.y += rotation.y;
        camera->rotation.z += rotation.z;


        double speed = 7.0 * (dt + .1f);

        picg_vec3F movement = {0.f, 0.f, 0.f};

        if(picg_keyboard_keydown("W"))
            movement.z += speed;

        if(picg_keyboard_keydown("A"))
            movement.x += speed;

        if(picg_keyboard_keydown("S"))
            movement.z -= speed;

        if(picg_keyboard_keydown("D"))
            movement.x -= speed;

        if(picg_keyboard_keydown("space"))
            movement.y -= speed;

        if(picg_keyboard_keydown("x"))
            movement.y += speed;

        picg_vec3F rotated = picg_transform_rotate(movement, camera->rotation);

        camera->position.x += rotated.x;
        camera->position.y += rotated.y;
        camera->position.z += rotated.z;

        for(int i = 0; i < N; ++i) {
            if(meshes[i]) {
                picg_mesh_render(meshes[i]);
            }

            if(physic[i]) {
                picg_physics_physicsComponent_debug_render(physic[i]);
            }
        }

        obj->rotation.x += 0.1;
        picg_mesh_render(obj);

        picg_window_display();

        dt = picg_ha_timer_gettime(&timer);

        sprintf(title, "Pic-g 3d engine, FPS: %f", 1.f / (float)picg_ha_timer_gettime(&timer));
        picg_window_setTitle(title);
    }


    /*
    Todo: all things like meshes should be freed
    */

    return 0;
}