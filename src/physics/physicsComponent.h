#pragma once
#include "../math/vector3D.h"
#include "../graphics/object/mesh.h"

#include "AABB.h"
#include <stdlib.h>   
#include <float.h>

typedef struct {
    picg_vec3F velocity;

    /*
        0/false = not moved by collision response
        1/true = affected
    */
    int isDynamic;

    picg_physics_AABB aabb;
} picg_physics_physicsComponent;

picg_physics_physicsComponent* picg_physics_physicsComponent_create() {
    picg_physics_physicsComponent* comp = (picg_physics_physicsComponent*)calloc(1, sizeof(picg_physics_physicsComponent));

    if(!comp) {
        printf("Error: physicsComponent.h, picg_physics_physicsComponent_create(), failed to create physicsComponent\n");
        return NULL;
    }

    return comp;
}

void picg_physics_physicsComponent_calculateAABB(picg_physics_AABB* aabb, picg_mesh* mesh) {
    if(mesh->vertexCount == 0 || !aabb || !mesh) {
        printf("Error: physicsComponent.h, picg_physics_physicsComponent_calculateAABB(), a field was null/empty\n");
        return;
    }

    // We need this to prevent weird behaviour
    aabb->minX = aabb->minY = aabb->minZ = FLT_MAX;
    aabb->maxX = aabb->maxY = aabb->maxZ = -FLT_MAX;

    for(int i = 0; i < mesh->vertexCount; ++i) {
        // now calculate min and max coordinates of all of these
        picg_vertex3F vertex = {
            mesh->position.x + mesh->vertices[i].x,
            mesh->position.y + mesh->vertices[i].y,
            mesh->position.z + mesh->vertices[i].z
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
    glPushMatrix();

    glBegin(GL_POINTS);

    glColor3f(1.f, 0.f, 1.f);

    // TODO: rendering
    glVertex3f(comp->aabb.minX, comp->aabb.minY, comp->aabb.minZ);
    glVertex3f(comp->aabb.minX, comp->aabb.minY, comp->aabb.maxZ);
    glVertex3f(comp->aabb.minX, comp->aabb.maxY, comp->aabb.minZ);
    glVertex3f(comp->aabb.minX, comp->aabb.maxY, comp->aabb.maxZ);
    glVertex3f(comp->aabb.maxX, comp->aabb.minY, comp->aabb.minZ);
    glVertex3f(comp->aabb.maxX, comp->aabb.minY, comp->aabb.maxZ);
    glVertex3f(comp->aabb.maxX, comp->aabb.maxY, comp->aabb.minZ);
    glVertex3f(comp->aabb.maxX, comp->aabb.maxY, comp->aabb.maxZ);


    glEnd();

    glPopMatrix();
}

void picg_physics_physicsComponent_solve(picg_physics_physicsComponent* comp1, picg_physics_physicsComponent* comp2) {
    
}