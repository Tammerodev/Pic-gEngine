#pragma once
#include "../mesh/mesh.h"
#include "../material/material.h"
#include "../../physics/physicsComponent.h"

#include "../../globals/macro.h"
#include "../../globals/runtime.h"

typedef struct {
    picg_mesh* mesh;
    picg_material* material;

    picg_physics_physicsComponent* physics;
} picg_physicsmodel;

void picg_physicsmodel_render(picg_physicsmodel*);
void picg_physicsmodel_update(picg_physicsmodel*);
