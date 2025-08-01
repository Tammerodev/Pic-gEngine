#pragma once
#include "../math/vector3D.h"
#include "../graphics/object/mesh.h"
#include "../graphics/debug.h"

#include "AABB.h"
#include <stdlib.h>   
#include <float.h>

typedef struct {
    picg_vec3F velocity;
    picg_vertex3F acceleration;

    // This should be a referebce to the visual things position, TODO: the memory safety is absolutely terrible
    picg_vec3F *position;

    /*
        0/false = not moved by collision response
        1/true = affected
    */
    int isDynamic;
    picg_bool isColliding;
    picg_bool grabbable;

    picg_physics_AABB aabb;
} picg_physics_physicsComponent;

picg_physics_physicsComponent* picg_physics_physicsComponent_create(picg_bool isDynamic);
void picg_physics_physicsComponent_calculateAABB(picg_physics_AABB* aabb, picg_mesh* mesh);
void picg_physics_physicsComponent_debug_render(picg_physics_physicsComponent* comp, picg_bool force);
void picg_physics_physicsComponent_solve(picg_physics_physicsComponent* comp1, picg_physics_physicsComponent* comp2);
void picg_physics_physicsComponent_update(picg_physics_physicsComponent* comp, picg_mesh* mesh);
picg_bool picg_physics_physicsComponent_isPointWithinAABB(picg_vec3F *point, picg_physics_physicsComponent* comp);