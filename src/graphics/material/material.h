#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float values[13];

    /* Values passed to glMaterialFv:
       0-3        ambient   (RGBA)
       4-7        diffuse   (RGBA)
       8-11       specular  (RGBA)
       12         shininess (0.f - 128.f)
    */
} picg_material;

picg_material* picg_material_create_loadFromFile(const char* filename) {
    /* Takes in MTL file and reads its values */

    /* Example file:
        newmtl Wood                         // Material name, not used for our purpose
        Ka 1.000000 1.000000 1.000000       // Ambient color RGB
        Kd 0.640000 0.640000 0.640000       // Diffuse color RGB (main color)
        Ks 0.500000 0.500000 0.500000       // Specular color RgB (reflections)
        Ns 96.078431                        // Specular highlights (0.f - 1000.f)
        Ni 1.000000                         // Light bending (1.0f = default)
        d 1.000000                          // Transparency  (1.0f = default)
        illum 0                             // Mostly useless
        map_Kd woodtexture.jpg              // Texture file
    */


    FILE* mtlFile;

    mtlFile = fopen(filename, "r");

    if(mtlFile == NULL) 
    {
        PICG_ERROR("Error loading MTL file!\n");
        return NULL;
    }

    const int bufferLength = 100;
    char buffer[bufferLength];

    while(fgets(buffer, bufferLength, mtlFile)) {
        printf("buffer");
    }

    fclose(mtlFile);
}