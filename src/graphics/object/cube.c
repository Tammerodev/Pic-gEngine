#include "objects.h"
#include <stdlib.h>

struct picg_vertex3F vertices[8] = {
        { -0.5f, -0.5f, -0.5f }, 
        {  0.5f, -0.5f, -0.5f }, 
        {  0.5f,  0.5f, -0.5f },  
        { -0.5f,  0.5f, -0.5f }, 
        { -0.5f, -0.5f,  0.5f },
        {  0.5f, -0.5f,  0.5f }, 
        {  0.5f,  0.5f,  0.5f }, 
        { -0.5f,  0.5f,  0.5f }
    };


picg_mesh* picg_cube_create() {
    picg_mesh* mesh = malloc(sizeof(picg_mesh));

    mesh->meshSize = 8;    
    mesh->renderType = GL_QUADS;
    mesh->vertices = vertices;

    mesh->position.x = 0;
    mesh->position.y = 0;
    mesh->position.z = 0;

    mesh->rotation.x = 0;
    mesh->rotation.y = 10;
    mesh->rotation.z = 0;

    return mesh;
}

void picg_cube_destroy(picg_mesh* mesh) {
    
}