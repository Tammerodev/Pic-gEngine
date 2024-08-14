#pragma once
#include "../../math/vertex3D.h"
#include "../../math/vector3D.h"

#include "GL/gl.h"

typedef struct {
    struct picg_vertex3F* vertices;
    unsigned long meshSize;

    GLenum renderType;

    struct picg_vec3F position;
    struct picg_vec3F rotation;
} picg_mesh;

void picg_mesh_render(picg_mesh *mesh);