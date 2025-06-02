#pragma once
#include "mesh.h"
#include <stdio.h>
#include <string.h>
#include "../../math/stringFunctions.h"

// Simple cube
picg_mesh* picg_cube_create();
void picg_cube_destroy(picg_mesh* mesh);


picg_mesh* picg_modelObj_create(const char*);