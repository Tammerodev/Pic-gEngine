#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "../../globals/macro.h"

typedef struct {
    float values[13];

    /* Values passed to glMaterialFv:
       0-3        ambient   (RGBA)
       4-7        diffuse   (RGBA)
       8-11       specular  (RGBA)
       12         shininess (0.f - 128.f)
    */
} picg_material;

picg_material* picg_material_create_loadFromFile(const char* filename);