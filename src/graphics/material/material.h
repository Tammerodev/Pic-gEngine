#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../globals/OS.h"

#if WINDOWS
    #include <io.h>
    #define F_OK 0
    #define access _access
#endif
#if LINUX 
    #include <unistd.h>
#endif


#include "../../globals/macro.h"
#include "../texture/texture.h"

typedef struct {
    /* Values passed to glMaterialFv:
       0-3        ambient   (RGBA)
       4-7        diffuse   (RGBA)
       8-11       specular  (RGBA)
       12         shininess (0.f - 128.f)
    */
    float values[13];

    picg_image* texture;
} picg_material;

picg_material* picg_material_create_loadFromFile(const char* filename);

void picg_material_bind(picg_material*);
void picg_material_unbind(picg_material*);
