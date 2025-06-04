#pragma once
#include "../../math/vertex3D.h"
#include "../../math/vector3D.h"
#include <stdio.h>
#include "../../globals/runtime.h"

#include "GL/gl.h"

typedef struct {
    unsigned char verticesPerFace;
    unsigned int verticeIndexes[4];
    unsigned int normalIndexes[4];
    unsigned char verticeCount;

    picg_bool hasNormals;
} picg_face;

typedef struct {
    picg_vertex3F* vertices;
    picg_face* faces;

    unsigned long vertexCount;
    unsigned long faceCount;

    GLenum renderType;

    picg_vec3F position;
    picg_vec3F rotation;
} picg_mesh;

void picg_mesh_render(picg_mesh *mesh);