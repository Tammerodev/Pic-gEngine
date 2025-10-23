#pragma once
#include <stdio.h>

#include "../../math/vertex3D.h"
#include "../../math/vector3D.h"
#include "../../globals/runtime.h"
#include "../../globals/macro.h"

#include "GL/gl.h"
#include "../graphicsGL.h"

typedef struct {
    unsigned char verticesPerFace;
    unsigned int verticeIndexes[4];
    unsigned int normalIndexes[4];
    unsigned int textureIndexes[4];
    
    unsigned char verticeCount;

    picg_bool hasNormals;
    picg_bool hasTexture;
} picg_face;

typedef struct {
    picg_vertex3F* vertices;
    picg_vertex3F* texcoords;
    picg_vertex3F* normals;

    picg_face* faces;

    unsigned long vertexCount;
    unsigned long texcoordCount;
    unsigned long normalsCount;

    unsigned long faceCount;

    GLenum renderType;

    picg_vec3F position;
    picg_vec3F rotation;
    picg_vec3F scaling;

    picg_bool render;
    
    // 0.f = fully opaque
    // 1.f = fully transparent
    float inv_alpha;


} picg_mesh;

void picg_mesh_render(picg_mesh *mesh);