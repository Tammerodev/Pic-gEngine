#pragma once
#include "../mesh/mesh.h"
#include "../material/material.h"

typedef struct {
    picg_mesh* mesh;
    picg_mesh* material;
} picg_model;