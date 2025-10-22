#pragma once
#include "../mesh/mesh.h"
#include "../material/material.h"

typedef struct {
    picg_mesh* mesh;
    picg_material* material;
} picg_model;

void picg_model_render(picg_model*);