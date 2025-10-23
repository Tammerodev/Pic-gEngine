#pragma once
#include <stdlib.h>
#include "mesh.h"

picg_vertex3F vertices[8] = {
        { -0.5f, -0.5f, -0.5f}, 
        {  0.5f, -0.5f, -0.5f}, 
        {  0.5f,  0.5f, -0.5f},  
        { -0.5f,  0.5f, -0.5f}, 
        { -0.5f, -0.5f,  0.5f},
        {  0.5f, -0.5f,  0.5f}, 
        {  0.5f,  0.5f,  0.5f}, 
        { -0.5f,  0.5f,  0.5f}
    };


picg_mesh* picg_mesh_cube_create() {
    picg_mesh* mesh = (picg_mesh*)calloc(1, sizeof(picg_vertex3F) * 10);

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