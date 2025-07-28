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

    picg_physics_AABB aabb;
} picg_physics_physicsComponent;

picg_physics_physicsComponent* picg_physics_physicsComponent_create(picg_bool isDynamic) {
    picg_physics_physicsComponent* comp = (picg_physics_physicsComponent*)calloc(1, sizeof(picg_physics_physicsComponent));
    comp->position = calloc(1, sizeof(picg_vec3F));

    if(!comp) {
        PICG_ERROR("Failed to create physicsComponent");
        return NULL;
    }

    comp->isDynamic = isDynamic;

    return comp;
}

void picg_physics_physicsComponent_calculateAABB(picg_physics_AABB* aabb, picg_mesh* mesh) {
    if(mesh->vertexCount == 0) 
    {
        PICG_ERROR("No vertices in mesh");
        return;
    }
    if(!aabb || !mesh) 
    {
        PICG_ERROR("A field was null/empty");
        return;
    }

    // We need this to prevent weird behaviour
    aabb->minX = aabb->minY = aabb->minZ = FLT_MAX;
    aabb->maxX = aabb->maxY = aabb->maxZ = -FLT_MAX;

    for(int i = 0; i < mesh->vertexCount; ++i) {
        // now calculate min and max coordinates of all of these
        picg_vertex3F vertex = {
            mesh->position.x + mesh->scaling.x * mesh->vertices[i].x,
            mesh->position.y + mesh->scaling.y * mesh->vertices[i].y,
            mesh->position.z + mesh->scaling.z * mesh->vertices[i].z
        };

        if(vertex.x < aabb->minX)
            aabb->minX = vertex.x;
        if(vertex.x > aabb->maxX)
            aabb->maxX = vertex.x;
        
        if(vertex.y < aabb->minY)
            aabb->minY = vertex.y;
        if(vertex.y > aabb->maxY)
            aabb->maxY = vertex.y;

        if(vertex.z < aabb->minZ)
            aabb->minZ = vertex.z;
        if(vertex.z > aabb->maxZ)
            aabb->maxZ = vertex.z;
    }
}

void picg_physics_physicsComponent_debug_render(picg_physics_physicsComponent* comp) {
    if(!g_runtime_debug) return;

    glPushMatrix();

    glColor3f(1.f, 1.f, 1.f);

    float d = 0.5f;

    // TODO: rendering
    picg_graphics_debug_point_render(comp->aabb.minX, comp->aabb.minY, comp->aabb.minZ, d);
    picg_graphics_debug_point_render(comp->aabb.minX, comp->aabb.minY, comp->aabb.maxZ, d);
    picg_graphics_debug_point_render(comp->aabb.minX, comp->aabb.maxY, comp->aabb.minZ, d);
    picg_graphics_debug_point_render(comp->aabb.minX, comp->aabb.maxY, comp->aabb.maxZ, d);
    picg_graphics_debug_point_render(comp->aabb.maxX, comp->aabb.minY, comp->aabb.minZ, d);
    picg_graphics_debug_point_render(comp->aabb.maxX, comp->aabb.minY, comp->aabb.maxZ, d);
    picg_graphics_debug_point_render(comp->aabb.maxX, comp->aabb.maxY, comp->aabb.minZ, d);
    picg_graphics_debug_point_render(comp->aabb.maxX, comp->aabb.maxY, comp->aabb.maxZ, d);


    glEnd();

    glPopMatrix();
}

void picg_physics_physicsComponent_solve(picg_physics_physicsComponent* comp1, picg_physics_physicsComponent* comp2) {
    if(!comp1 || !comp2) 
    {
        PICG_ERROR("Physicscomponent does not exist!");
        return;
    }

    if(!comp1->position || !comp2->position) {
        PICG_ERROR("Physicscomponents reference (comp->position*) was not initialized to the mesh");
    }

    if (comp1->aabb.maxX < comp2->aabb.minX || comp1->aabb.minX > comp2->aabb.maxX) return;
    if (comp1->aabb.maxY < comp2->aabb.minY || comp1->aabb.minY > comp2->aabb.maxY) return;
    if (comp1->aabb.maxZ < comp2->aabb.minZ || comp1->aabb.minZ > comp2->aabb.maxZ) return;

    comp1->isColliding = true;
    comp2->isColliding = true;

    float overlapX = fminf(comp1->aabb.maxX, comp2->aabb.maxX) - fmaxf(comp1->aabb.minX, comp2->aabb.minX);
    float overlapY = fminf(comp1->aabb.maxY, comp2->aabb.maxY) - fmaxf(comp1->aabb.minY, comp2->aabb.minY);
    float overlapZ = fminf(comp1->aabb.maxZ, comp2->aabb.maxZ) - fmaxf(comp1->aabb.minZ, comp2->aabb.minZ);

    if(comp1->isDynamic && !comp2->isDynamic) {
        // Find the axis of least penetration
        if (overlapX < overlapY && overlapX < overlapZ) {
            // Resolve along X
            if (comp1->aabb.minX < comp2->aabb.minX)
                comp1->position->x -= overlapX;
            else
                comp1->position->x += overlapX;
            comp1->velocity.x = 0.f;
        } else if (overlapY < overlapZ) {
            // Resolve along Y
            if (comp1->aabb.minY < comp2->aabb.minY)
                comp1->position->y -= overlapY;
            else
                comp1->position->y += overlapY;
            comp1->velocity.y = 0.f;
        } else {
            // Resolve along Z
            if (comp1->aabb.minZ < comp2->aabb.minZ)
                comp1->position->z -= overlapZ;
            else
                comp1->position->z += overlapZ;
            comp1->velocity.z = 0.f;
        }
    } else if(comp1->isDynamic && comp2->isDynamic) {
        if (overlapX < overlapY && overlapX < overlapZ) {
            // Resolve along X
            if (comp1->aabb.minX < comp2->aabb.minX) {
                comp1->position->x -= overlapX / 2.f;
                comp2->position->x += overlapX / 2.f;
            } else {
                comp1->position->x += overlapX / 2.f;
                comp2->position->x -= overlapX / 2.f;
            }
            comp1->velocity.x = 0.f;
            comp2->velocity.x = 0.f;
        } else if (overlapY < overlapZ) {
            // Resolve along Y
            if (comp1->aabb.minY < comp2->aabb.minY) {
                comp1->position->y -= overlapY / 2.f;
                comp2->position->y += overlapY / 2.f;
            } else {
                comp1->position->y += overlapY;
                comp2->position->y -= overlapY / 2.f;
            }
            comp1->velocity.y = 0.f;
            comp2->velocity.y = 0.f;
        } else {
            // Resolve along Z
            if (comp1->aabb.minZ < comp2->aabb.minZ) {
                comp1->position->z -= overlapZ / 2.f;
                comp2->position->z += overlapZ / 2.f;
            } else {
                comp1->position->z += overlapZ / 2.f;
                comp2->position->z -= overlapZ / 2.f;
            }
            comp1->velocity.z = 0.f;
            comp2->velocity.z = 0.f;
        }

    }
}


void picg_physics_physicsComponent_update(picg_physics_physicsComponent* comp, picg_mesh* mesh) {
    comp->position = &mesh->position;

    if(!comp->position) {
        PICG_ERROR("Physicscomponents reference (comp->position*) was not initialized to the mesh");
        return;
    }

    // Gravity
    comp->acceleration.y = -0.01f;
    
    // Calculations
    comp->velocity.x += comp->acceleration.x;
    comp->velocity.y += comp->acceleration.y;
    comp->velocity.z += comp->acceleration.z;

    // Update position
    comp->position->x += comp->velocity.x;
    comp->position->y += comp->velocity.y;
    comp->position->z += comp->velocity.z;

    comp->isColliding = false;

    // Recalc AABB
    picg_physics_physicsComponent_calculateAABB(&comp->aabb, mesh);
}

picg_bool picg_physics_physicsComponent_isPointWithinAABB(picg_vec3F *point, picg_physics_physicsComponent* comp) {
    if(!point || !comp) PICG_ERROR("Null vector or physicscomponent!");

    if(point->x > comp->aabb.maxX) return false;
    if(point->x < comp->aabb.minX) return false;


    if(point->y > comp->aabb.maxY) return false;
    if(point->y < comp->aabb.minY) return false;

    if(point->z > comp->aabb.maxZ) return false;
    if(point->z < comp->aabb.minZ) return false;

    return true;
}