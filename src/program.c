#include <program.h>


#include <stdio.h>

#include <globals/runtime.h>
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

#define N 50

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

picg_mesh* sideways = NULL;
picg_mesh* plane = NULL;
picg_mesh* obj = NULL;
picg_mesh* ground = NULL;

picg_mesh* player_hitbox = NULL;

picg_physics_physicsComponent* plane_physics = NULL;
picg_physics_physicsComponent* sideways_physics = NULL;
picg_physics_physicsComponent* ground_physics = NULL;

picg_physics_physicsComponent* player_physics = NULL;


picg_image img;
picg_image floor_wood_img;
picg_image grass_img;


//
picg_bool initialized = false;


int program_init()
{
    const int sizeX = 1500;
    const int sizeY = 900;

    // Create & init graphics 
    picg_window_create(sizeX, sizeY, "Pic-g 3D engine", 0);
    picg_gl_init3D(sizeX, sizeY);
    picg_gl_setClearColor(0.0f, 0.0f, 0.0f, 1.f);

    // Make a grid of cubes (size=N)
    float x = 0.f;
    float z = 0.f;

    for(int i = 0; i < N; i++) {
        picg_mesh* mesh = NULL;

        mesh = picg_modelObj_create("dev/Models/cube.obj");

        meshes[i] = mesh;
        meshes[i]->position.x = x*10.f;

        x += 1.f;
        if(x > (int)sqrt(N)) {
            x = 0.f;
            z += 5.f;
        }

        float x = (float)rand()/(float)(RAND_MAX/4.5f);

        meshes[i]->position.z = z + x;
        meshes[i]->position.y += 100.f + sin(x / 12.f) * 22.5f;
        
        // physics
        physic[i] = picg_physics_physicsComponent_create(true);
        picg_physics_physicsComponent_calculateAABB(&physic[i]->aabb, meshes[i]);
    } 

    ground = picg_modelObj_create("dev/Models/ground.obj"); 
    ground_physics = picg_physics_physicsComponent_create(false);
    picg_physics_physicsComponent_calculateAABB(&ground_physics->aabb, ground);
    ground->position.y -= 100.f;

    plane = picg_modelObj_create("dev/Models/plane.obj"); 
    plane_physics = picg_physics_physicsComponent_create(false);
    picg_physics_physicsComponent_calculateAABB(&plane_physics->aabb, plane);

    sideways = picg_modelObj_create("dev/Models/sideways.obj"); 
    sideways_physics = picg_physics_physicsComponent_create(false);
    picg_physics_physicsComponent_calculateAABB(&sideways_physics->aabb, sideways);

    {
            // PLAYER
        player_hitbox = picg_modelObj_create("dev/Models/cube.obj"); 
        player_hitbox->scaling.y = 10.f;
        player_hitbox->scaling.x = 3.f;
        player_hitbox->scaling.z = 3.f;

        player_physics = picg_physics_physicsComponent_create(true);
        picg_physics_physicsComponent_calculateAABB(&player_physics->aabb, player_hitbox);
    }

    // Teapot
    obj = picg_modelObj_create("/home/lauri/Downloads/leopard-2-mbt-revolution/source/chassis.obj"); 
    obj->scaling.x = 10.f;
    obj->scaling.y = 10.f;
    obj->scaling.z = 10.f;
    obj->position.y -= 90.f;
    obj->position.x -= 100.f;

    // Create the camera
    camera = picg_camera_create();

    glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable light #1
	glEnable(GL_NORMALIZE); 

    // IMAGE/TEXTURE LOADING

    img = picg_image_load("/home/lauri/Downloads/leopard-2-mbt-revolution/textures/mbt_03_ext01_blufor_co.png");
    picg_texture_load(&img);

    floor_wood_img = picg_image_load("dev/Models/tex/floor_wood.jpg");
    picg_texture_load(&floor_wood_img);

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
        camera->rotation.y += mouse_change.x / 5.f;
        camera->rotation.x += mouse_change.y / 5.f;
        picg_window_mouse_setPosition((picg_vec2I){windowSize.x / 2, windowSize.y / 2});
    }

    g_runtime_debug = 0;
    if(picg_keyboard_keydown("p"))
        g_runtime_debug = 1;

    double speed = 6.0 * (dt + .1f);

    picg_vec3F movement = {0.f, 0.f, 0.f};

    if(picg_keyboard_keydown("W"))
        movement.z -= speed;

    if(picg_keyboard_keydown("A"))
        movement.x -= speed;

    if(picg_keyboard_keydown("S"))
        movement.z += speed;

    if(picg_keyboard_keydown("D"))
        movement.x += speed;

    if(picg_keyboard_keydown("space") && player_physics->isColliding)
        player_physics->velocity.y = 0.5f;

    if(picg_keyboard_keydown("x"))
            movement.y -= speed;

    picg_vec3F rotated = picg_transform_rotate(movement, camera->rotation);

    player_hitbox->position.x += rotated.x;
    player_hitbox->position.z += rotated.z;

    for(int i = 0; i < N; ++i) {
        if(physic[i]) {
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
            picg_physics_physicsComponent_solve(physic[i], sideways_physics);

            // custom collisions
            picg_physics_physicsComponent_calculateAABB(&physic[i]->aabb, meshes[i]);
            picg_physics_physicsComponent_solve(physic[i], plane_physics);

            picg_physics_physicsComponent_calculateAABB(&physic[i]->aabb, meshes[i]);
            picg_physics_physicsComponent_solve(physic[i], ground_physics);

            picg_physics_physicsComponent_calculateAABB(&physic[i]->aabb, meshes[i]);
            picg_physics_physicsComponent_solve(physic[i], player_physics);
        }
    }

    // Plane demo
    plane->position.z -= 0.1f;
    sideways->position.z -= 0.1f;
    sideways->position.x -= 0.1f;

    picg_physics_physicsComponent_calculateAABB(&plane_physics->aabb, plane);
    picg_physics_physicsComponent_calculateAABB(&sideways_physics->aabb, sideways);
    picg_physics_physicsComponent_calculateAABB(&ground_physics->aabb, ground);

    {

        picg_physics_physicsComponent_update(player_physics, player_hitbox);

        picg_physics_physicsComponent_solve(player_physics, ground_physics);

        picg_physics_physicsComponent_calculateAABB(&player_physics->aabb, player_hitbox);
        picg_physics_physicsComponent_solve(player_physics, plane_physics);

        picg_physics_physicsComponent_calculateAABB(&player_physics->aabb, player_hitbox);
        picg_physics_physicsComponent_solve(player_physics, sideways_physics);

    }

    sprintf(title, "Pic-g 3d engine, FPS: %f", 1.f / (float)picg_ha_timer_gettime(&timer));
    picg_window_setTitle(title);
    
    camera->position.x = -player_hitbox->position.x;
    camera->position.y = -player_hitbox->position.y;
    camera->position.z = -player_hitbox->position.z;

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


    if(picg_keyboard_keydown("F")) {
        GLfloat lightColor2[] = {1.0f, 1.0f, 1.0f, 1.0f}; //Color (0.5, 0.5, 0.5)
        GLfloat lightPos2[] = {player_hitbox->position.x, player_hitbox->position.y, player_hitbox->position.z, 1.f}; //Positioned at (4, 0, 8)

        picg_addlight_diffuse(2, lightColor2, lightPos2);
    } else {
        picg_disablelight(2);
    }



    for(int i = 0; i < N; ++i) {
        if(physic[i])
            picg_physics_physicsComponent_debug_render(physic[i]);

        if(meshes[i]) {
            picg_mesh_render(meshes[i]);
        }
    }

    picg_texture_bind(&grass_img);
    picg_mesh_render(ground);
    picg_texture_unbind();

    // TANK
    picg_texture_bind(&img);
    picg_mesh_render(obj);
    picg_texture_unbind();

    picg_texture_bind(&floor_wood_img);
    picg_mesh_render(plane);
    picg_mesh_render(sideways);
    picg_texture_unbind();

    if(g_runtime_debug)
    {
        glColor3f(1.f, 1.f, 1.f);
        picg_graphics_debug_point_render(0.f, 0.f, 0.f, 100.f);
    }

    picg_physics_physicsComponent_debug_render(sideways_physics);
    picg_physics_physicsComponent_debug_render(plane_physics);
    picg_physics_physicsComponent_debug_render(player_physics);


    picg_window_display();
    return 0;
}

int program_close()
{
    return 0;
}
