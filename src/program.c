#include <program.h>


#include <stdio.h>

#include "globals/runtime.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <window/window.h>
#include <graphics/graphicsGL.h>
#include <graphics/object/objects.h>
#include <graphics/lighting/lightSource.h>
#include <graphics/camera/camera.h>
#include <graphics/debug.h>
#include <physics/physicsComponent.h>
#include <math/timer.h>
#include <math/transforms.h>
#include <math.h>
#include <graphics/texture/image.h>
#include <graphics/texture/texture.h>
#include <physics/raycast.h>

#define NPlayer 0
#define N 1

// Delta time
picg_ha_timer timer = {};
double dt = 0.0;

char title[48];

int persist_pos_x = 0;
int persist_pos_y = 0;
picg_vec3F rotation = {0.f, 0.f, 0.f};

// 3D
picg_camera* camera = NULL;
picg_mesh* meshes[N];
picg_physics_physicsComponent* physic[N];

// Ground
picg_mesh* ground = NULL;
picg_physics_physicsComponent* ground_physics = NULL;
picg_image grass_img;

// Antenna mast
picg_mesh* antenna_mast = NULL;
picg_physics_physicsComponent* antenna_mast_physics = NULL;
picg_image metal_beam_img;

// Antenna yagi
picg_mesh* antenna = NULL;

picg_bool initialized = false;


// sky
#define COUNT_STARS 500
picg_mesh* stars_meshes[COUNT_STARS];

const int sizeX = 1500;
const int sizeY = 900;

int program_init()
{

    // Create & init graphics 
    picg_window_create(sizeX, sizeY, "Pic-g 3D engine", 0);
    picg_gl_init3D(sizeX, sizeY);
    picg_gl_setClearColor(.07f, 0.07f, 0.15f, 1.f);

    // Make a grid of cubes (size=N)
    float x = 0.f;
    float z = 0.f;

    for(int i = 0; i < COUNT_STARS; i++) {
        picg_mesh *star = NULL;
        star = picg_modelObj_create("dev/Models/dot.obj");

        stars_meshes[i] = star;

        const float radius = 100000.f;

        float u = (float)rand() / RAND_MAX;
        float v = (float)rand() / RAND_MAX;

        float theta = 2.0f * 3.1415927f * u;
        float phi = acosf(2.0f * v - 1.0f);
        float r = sinf(phi);

        float x = r * cosf(theta);
        float y = cosf(phi);
        float z_pos = r * sinf(theta);

        stars_meshes[i]->position.x = radius * x;
        stars_meshes[i]->position.y = radius * y - 100.f;
        stars_meshes[i]->position.z = radius * z_pos;

        stars_meshes[i]->rotation.x = (float)rand() / RAND_MAX * 100.f;
        stars_meshes[i]->rotation.y = (float)rand() / RAND_MAX * 100.f;
        stars_meshes[i]->rotation.z = (float)rand() / RAND_MAX * 100.f;
    }

    ground = picg_modelObj_create("dev/Models/ground.obj"); 
    ground_physics = picg_physics_physicsComponent_create(false);
    picg_physics_physicsComponent_calculateAABB(&ground_physics->aabb, ground);

    antenna_mast = picg_modelObj_create("dev/demos/demo_209/mast.obj");
    antenna_mast_physics = picg_physics_physicsComponent_create(false);
    picg_physics_physicsComponent_calculateAABB(&antenna_mast_physics->aabb, antenna_mast);

    antenna = picg_modelObj_create("dev/demos/demo_209/antenna.obj");
    antenna->position.y = 175.f;

    {
        // PLAYER
        meshes[NPlayer] = picg_modelObj_create("dev/Models/cube.obj"); 
        meshes[NPlayer]->scaling.y = 3.f;
        meshes[NPlayer]->scaling.x = 1.f;
        meshes[NPlayer]->scaling.z = 1.f;
        meshes[NPlayer]->position.y = 400.f;

        meshes[NPlayer]->render = false;

        physic[NPlayer] = picg_physics_physicsComponent_create(true);
        picg_physics_physicsComponent_calculateAABB(&physic[NPlayer]->aabb, meshes[NPlayer]);

        if(!physic[NPlayer] || !meshes[NPlayer]) {
            PICG_ERROR("Couldnt create player physics!");
            abort();
        }
    }

    // Create the camera
    camera = picg_camera_create();
    camera->position.y = -30.f;
    camera->position.z = -400.f;

    // IMAGE/TEXTURE LOADING
    grass_img = picg_image_load("dev/Models/tex/grass.jpg");
    picg_texture_load(&grass_img);

    ///////////////////////////

    initialized = true;

    return 0;
}

picg_vec2I mouse;

int program_update()
{
    if(!initialized) 
    {
        PICG_ERROR("Not initialized!");
        return -1;
    }

    dt = picg_ha_timer_gettime(&timer);
    picg_ha_timer_reset(&timer);
    picg_ha_timer_start(&timer);

    picg_vec2I mouse = picg_window_mouse_getPosition();
    picg_vec2I windowPos = picg_window_getPosition(); 
    picg_vec2I windowSize = picg_window_getSize();

    picg_vec2I center = {
        windowPos.x + windowSize.x / 2,
        windowPos.y + windowSize.y / 2
    };

    picg_vec2I mouse_change = {
        mouse.x - center.x,
        mouse.y - center.y
    };

    if (mouse_change.x != 0 || mouse_change.y != 0) {
        camera->rotation.y += mouse_change.x / 10.f;
        camera->rotation.x += mouse_change.y / 10.f;

        picg_window_mouse_setPosition((picg_vec2I){windowSize.x / 2, windowSize.y / 2});
    }

    g_runtime_debug = 0;
    if(picg_keyboard_keydown("p"))
        g_runtime_debug = 1;

    double speed = 2.0 * (dt + .1f);

    picg_vec3F movement = {0.f, 0.f, 0.f};

    if(picg_keyboard_keydown("W"))
        movement.z -= speed;

    if(picg_keyboard_keydown("A"))
        movement.x -= speed;

    if(picg_keyboard_keydown("S"))
        movement.z += speed;

    if(picg_keyboard_keydown("D"))
        movement.x += speed;

    if(picg_keyboard_keydown("Y"))
        physic[NPlayer]->velocity.y = 3.f;

    if(picg_keyboard_keydown("space") && physic[NPlayer]->isColliding)
        physic[NPlayer]->velocity.y = 0.25f;
        
    // Only yaw is relevant for this
    const picg_vec3F cam_rot_mv = {0.f, camera->rotation.y, 0.f};
    picg_vec3F transformed_movement = picg_transform_rotate(movement, cam_rot_mv);

    meshes[NPlayer]->position.x += transformed_movement.x;
    meshes[NPlayer]->position.z += transformed_movement.z;

    picg_physics_physicsComponent_update(physic[NPlayer], meshes[NPlayer]);

    for(int i = 0; i < N; ++i) {
        if(physic[i] && meshes[i]) {
            picg_physics_physicsComponent_update(physic[i], meshes[i]);

            // Collisions with other cubes
            for(int j = 0; j < N; ++j) {
                if(j != i) {
                    picg_physics_physicsComponent_calculateAABB(&physic[i]->aabb, meshes[i]);
                    picg_physics_physicsComponent_calculateAABB(&physic[j]->aabb, meshes[j]);

                    picg_physics_physicsComponent_solve(physic[i], physic[j]);
                }
            }

            picg_physics_physicsComponent_calculateAABB(&physic[i]->aabb, meshes[i]);
                picg_physics_physicsComponent_solve(physic[i], ground_physics);

            picg_physics_physicsComponent_calculateAABB(&physic[i]->aabb, meshes[i]);
                picg_physics_physicsComponent_solve(physic[i], antenna_mast_physics);
        } else {
            PICG_ERROR("Null physicsComponent/mesh");
        }
    }

    picg_physics_physicsComponent_calculateAABB(&ground_physics->aabb, ground);

    sprintf(title, "Pic-g 3d engine, FPS: %f", 1.f / (float)picg_ha_timer_gettime(&timer));
    picg_window_setTitle(title);
    
    camera->position.x = -meshes[NPlayer]->position.x;
    camera->position.y = -meshes[NPlayer]->position.y;
    camera->position.z = -meshes[NPlayer]->position.z;

    return 0;
}

int program_render()
{
    picg_gl_clear();

    glMatrixMode(GL_MODELVIEW);
    picg_camera_apply(camera);
    
    GLfloat ambientColor[] = {0.1f, 0.1f, 0.1f, 1.0f}; //Color (0.2, 0.2, 0.2)
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
    
    GLfloat lightColor0[] = {0.4f, 0.4f, 0.4f, 0.7f}; //Color (0.5, 0.5, 0.5)
    GLfloat lightPos0[] = {0.0f, 50.0f, 0.0f, 1.0f}; //Positioned at (4, 0, 8)

    picg_addlight_diffuse(0, lightColor0, lightPos0);
    picg_addlight_diffuse(1, lightColor0, lightPos0);


    if(!picg_keyboard_keydown("F")) {
        GLfloat lightColor2[] = {1.0f, 1.0f, 1.0f, 1.0f}; //Color (0.5, 0.5, 0.5)
        GLfloat lightPos2[] = {meshes[NPlayer]->position.x, meshes[NPlayer]->position.y, meshes[NPlayer]->position.z, 1.f}; //Positioned at (4, 0, 8)

        picg_addlight_diffuse(2, lightColor2, lightPos2);
    } else {
        picg_disablelight(2);
    }

    if (picg_keyboard_keydown("J")) {
        float pitch = camera->rotation.x * (3.14159265f / 180.0f);
        float yaw   = camera->rotation.y * (3.14159265f / 180.0f);

        // Calculate forward direction vector from pitch and yaw
        picg_vec3F dir;
        dir.x = cosf(pitch) * sinf(yaw);
        dir.y = -sinf(pitch);
        dir.z = -cosf(pitch) * cosf(yaw);

        const picg_vec3F start = {
            meshes[NPlayer]->position.x,
            meshes[NPlayer]->position.y - 1.f,
            meshes[NPlayer]->position.z
        };

        picg_physics_raycast_return ret_ = picg_physics_raycast_cast(start, dir, 1000, physic, N, 1.f);
        
        if (ret_.NComponent >= 0 && ret_.NComponent < N) {
            // valid hit
            float halfX = (physic[ret_.NComponent]->aabb.maxX - physic[ret_.NComponent]->aabb.minX) / 2.f;
            float halfY = (physic[ret_.NComponent]->aabb.maxY - physic[ret_.NComponent]->aabb.minY) / 2.f;
            float halfZ = (physic[ret_.NComponent]->aabb.maxZ - physic[ret_.NComponent]->aabb.minZ) / 2.f;

            picg_physics_physicsComponent_debug_render(physic[ret_.NComponent], true);

            meshes[ret_.NComponent]->position = (picg_vec3F) {
                ret_.collision_position.x + dir.x * halfX,
                ret_.collision_position.y + dir.y * halfY,
                ret_.collision_position.z + dir.z * halfZ
            };

            if (picg_keyboard_keydown("K")) {
                physic[ret_.NComponent]->velocity.x = dir.x * 2.f;
                physic[ret_.NComponent]->velocity.y = dir.y * 2.f;
                physic[ret_.NComponent]->velocity.z = dir.z * 2.f;

            }

        }
    }


    for(int i = 0; i < N; ++i) {
        if(physic[i])
            picg_physics_physicsComponent_debug_render(physic[i], false);

        if(meshes[i]) {
            picg_mesh_render(meshes[i]);
        }
    }

    glDisable(GL_LIGHTING);
    for(int i = 0; i < COUNT_STARS; ++i) {
        if(stars_meshes[i]) {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glEnable(GL_POINT_SMOOTH);
            glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

            picg_mesh_render(stars_meshes[i]);

            glDisable(GL_POINT_SMOOTH);
            glDisable(GL_BLEND);

            if(stars_meshes[i]->rotation.x > 26.f && stars_meshes[i]->rotation.x < 30.f) {
                stars_meshes[i]->position.x += (stars_meshes[i]->rotation.y - 45.f) / 4.f;
                stars_meshes[i]->position.y += (stars_meshes[i]->rotation.z - 45.f) / 4.f;
            }
        }
    }
    glEnable(GL_LIGHTING);

    picg_texture_bind(&grass_img);
    picg_mesh_render(ground);
    picg_texture_unbind();

    picg_mesh_render(antenna_mast);
    picg_mesh_render(antenna);


    if(g_runtime_debug)
    {
        glColor3f(1.f, 1.f, 1.f);
        picg_graphics_debug_point_render(0.f, 0.f, 0.f, 100.f);
    }

    picg_physics_physicsComponent_debug_render(physic[NPlayer], false);


    picg_window_display();
    return 0;
}

int program_close()
{
    return 0;
}