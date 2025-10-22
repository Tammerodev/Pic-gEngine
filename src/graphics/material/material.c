#include "material.h"

picg_image* texture_image = NULL;
char material_tex_filename[100];


int loadMTL(const char *filepath_mtl) {
    FILE* mtlFile;
    mtlFile = fopen(filepath_mtl, "r");

    if(mtlFile == NULL) 
    {
        PICG_ERROR("Error loading MTL file!\n");
        return 1;
    }

    const int bufferLength = 100;
    char buffer[bufferLength];

    material_tex_filename[0] = '\0';    // In case texture filepath is not found, this will terminate the array.  

    while(fgets(buffer, bufferLength, mtlFile)) {
        printf(buffer);

        if(buffer[0] == '#') {
            // Comment, continue.
            continue;
        } else
        if(buffer[0] == 'K') {
            // Color setting
        } else
        if(buffer[0] == 'N') {
            // Optics setting
        } else
        if(buffer[0] == 'm' && buffer[1] == 'a' && buffer[2] == 'p') {
            // Texture filename. Actual filepath begins at index 6.
            // This code is also to make sure, the newline character (\n) is not included in the material_tex_filename
            const int starting_index = 7;
            int char_index = 0;

            char curr_char = buffer[char_index + starting_index];
            material_tex_filename[char_index] = curr_char;

            while(buffer[char_index + starting_index + 1] != '\0' && buffer[char_index + starting_index + 1] != '\n') {
                char_index++;

                curr_char = buffer[char_index + starting_index];

                material_tex_filename[char_index] = curr_char;

                PICG_LOG("%i\n", curr_char);
            }
        }   
    }

    fclose(mtlFile);

    return 0;
}

int loadMTLtexture() {
    printf("MATFILENAME (LOADING): %s... \n", material_tex_filename);

    picg_image texture_image_stack = picg_image_load(material_tex_filename);

    texture_image = (picg_image*)calloc(sizeof(texture_image_stack), 1);

    *texture_image = texture_image_stack;

    if(texture_image == NULL) {
        PICG_ERROR("Texture (heap allocated) failed to be assigned to texture (stack allocated).");
        return 1;
    } else {
        picg_texture_load(texture_image);
    }

    return 0;
}

void loadMTLfree()
{
    texture_image = NULL;
}

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

    if (!access(filepath_mtl, F_OK) == 0) {
        return NULL;
    }

    if(loadMTL(filepath_mtl)) {
        // error
        PICG_ERROR("loadMTL() failed");
    }

    if(material_tex_filename[0] != '\0') {
        loadMTLtexture();
    }

    // Create material
    picg_material* material = calloc(sizeof(picg_material) + sizeof(texture_image) + 1, 1);
    
    if(material_tex_filename[0] != '\0') {
        material->texture = texture_image;
    }

    // Return initialized picg_material
    return material;
}

void picg_material_bind(picg_material *mat)
{
    if(mat == NULL) {
        PICG_ERROR("Material data null");
        return;
    }

    if(!mat->texture) {
        PICG_ERROR("Material texture data null");
        return;
    }

    // Has a texture
    picg_texture_bind(mat->texture);

    // TODO: glMaterialfv(...)
}

void picg_material_unbind(picg_material *mat)
{
    if(!mat) {
        PICG_ERROR("Material data null");
        return;
    }

    if(!mat->texture) {
        PICG_ERROR("Material texture data null");
        return;
    }
    // Has a texture
        
    picg_texture_unbind();
}
