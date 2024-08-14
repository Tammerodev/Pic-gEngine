#pragma once
#include "../../math/vertex3D.h"
#include "../../math/vector3D.h"

#include "GL/gl.h"

struct picg_mesh {
    struct picg_vertex3F* vertices;
    unsigned long meshSize;

    GLenum renderType;

    struct picg_vec3F position;
    struct picg_vec3F rotation;
};

void picg_mesh_render(struct picg_mesh *mesh);