#include "objects.h"
#include <stdlib.h>

struct picg_vertex3F vertices[8] = {
        { -0.5f, -0.5f, -0.5f,       0.2, 0.4, 0.0, 1.0}, 
        {  0.5f, -0.5f, -0.5f,       0.6, 0.8, 0.8, 1.0 }, 
        {  0.5f,  0.5f, -0.5f,       0.3, 0.2, 0.3, 1.0 },  
        { -0.5f,  0.5f, -0.5f,       0.8, 0.4, 0.4, 1.0 }, 
        { -0.5f, -0.5f,  0.5f,       0.1, 0.8, 0.8, 1.0 },
        {  0.5f, -0.5f,  0.5f,       0.0, 0.5, 0.5, 1.0 }, 
        {  0.5f,  0.5f,  0.5f,       0.3, 0.6, 0.9, 1.0 }, 
        { -0.5f,  0.5f,  0.5f,       0.2, 0.4, 0.2, 1.0 }
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