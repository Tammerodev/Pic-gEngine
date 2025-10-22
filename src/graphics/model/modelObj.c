#include "objects.h"
#include "../mesh/meshObj.h"

/* 
    Loads vertex and material data, returns picg_model
*/

picg_model* picg_modelObj_create(const char* filepath) {
    picg_mesh* modelmesh = picg_meshObj_create(filepath);
    picg_material *modelmaterial = picg_material_create_loadFromFile(filepath);

    picg_model* model = (picg_model*)calloc(sizeof(modelmesh) + sizeof(modelmaterial), 1);

    if(modelmesh == NULL) {
        PICG_ERROR("OBJ Model mesh failed to load");
        return NULL;
    }

    if(modelmaterial == NULL) {
        PICG_ERROR("OBJ Model MTL (material) failed to load");
    }

    model->mesh = modelmesh;

    return model;
}