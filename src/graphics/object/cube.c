#include "objects.h"

struct picg_mesh* picg_cube_create() {
    struct picg_mesh* mesh;

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
    
    mesh->renderType = GL_TRIANGLES;
    mesh->vertices = vertices;
}

struct picg_mesh* picg_cube_destroy() {
    
}