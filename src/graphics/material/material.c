#include "material.h"

picg_material *picg_material_create_loadFromFile(const char *filepath_obj)
{
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

    // Copy filepath and replace .obj ending with .mtl in the copy
    size_t filepath_obj_length = strlen(filepath_obj);
    char *filepath_mtl = malloc(filepath_obj_length + 1);
    strcpy(filepath_mtl, filepath_obj);

    if(filepath_mtl) {
        filepath_mtl[filepath_obj_length - 4] = '.';
        filepath_mtl[filepath_obj_length - 3] = 'm';
        filepath_mtl[filepath_obj_length - 2] = 't';
        filepath_mtl[filepath_obj_length - 1] = 'l';
    }


    FILE* mtlFile;
    mtlFile = fopen(filepath_mtl, "r");

    if(mtlFile == NULL) 
    {
        PICG_ERROR("Error loading MTL file!\n");
        return NULL;
    }

    const int bufferLength = 100;
    char buffer[bufferLength];

    while(fgets(buffer, bufferLength, mtlFile)) {
        printf(buffer);
    }

    fclose(mtlFile);
}
