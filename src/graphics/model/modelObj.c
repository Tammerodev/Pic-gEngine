#include "objects.h"
#include "../mesh/meshObj.h"

/* 
    Loads vertex and material data, returns picg_model
*/

picg_model* picg_modelObj_create(const char* filepath) {
    picg_mesh* modelmesh = picg_meshObj_create(filepath);

    // Note: later add modelmaterial size to calloc size calc.
    picg_model* model = (picg_model*)calloc(sizeof(modelmesh), 1);

    if(modelmesh == NULL) {
        PICG_ERROR("Model OBJ mesh failed to load");
        return NULL;
    }

    model->mesh = modelmesh;

    return model;
}