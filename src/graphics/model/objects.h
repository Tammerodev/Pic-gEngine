#pragma once
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "../mesh/mesh.h"
#include "../../math/stringFunctions.h"

#include "model.h"  
#include "physicsmodel.h"  

// Simple cube
picg_mesh* picg_cube_create();
void picg_cube_destroy(picg_mesh* mesh);

// Mesh
picg_model* picg_modelObj_create(const char*);
picg_physicsmodel* picg_physicsmodelObj_create(const char*, picg_bool);

