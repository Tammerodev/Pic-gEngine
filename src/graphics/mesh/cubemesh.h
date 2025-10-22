#pragma once
#include <stdlib.h>
#include "mesh.h"

picg_vertex3F vertices[8] = {
        { -0.5f, -0.5f, -0.5f,       0.2, 0.4, 0.0, 1.0}, 
        {  0.5f, -0.5f, -0.5f,       0.6, 0.8, 0.8, 1.0 }, 
        {  0.5f,  0.5f, -0.5f,       0.3, 0.2, 0.3, 1.0 },  
        { -0.5f,  0.5f, -0.5f,       0.8, 0.4, 0.4, 1.0 }, 
        { -0.5f, -0.5f,  0.5f,       0.1, 0.8, 0.8, 1.0 },
        {  0.5f, -0.5f,  0.5f,       0.0, 0.5, 0.5, 1.0 }, 
        {  0.5f,  0.5f,  0.5f,       0.3, 0.6, 0.9, 1.0 }, 
        { -0.5f,  0.5f,  0.5f,       0.2, 0.4, 0.2, 1.0 }
    };


picg_mesh* picg_mesh_cube_create() {
    picg_mesh* mesh = (picg_mesh*)calloc(1, sizeof(picg_vertex3F) * 8);

    mesh->vertexCount = 8;    
    mesh->renderType = GL_QUADS;
    mesh->vertices = vertices;

    mesh->scaling.x = 1.f;
    mesh->scaling.y = 1.f;
    mesh->scaling.z = 1.f;
    
    mesh->render = true;

    return mesh;
}

void picg_mesh_cube_destroy(picg_mesh* mesh) {
    
}