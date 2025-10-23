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
    model->material = modelmaterial;

    return model;
}


picg_physicsmodel* picg_physicsmodelObj_create(const char* filepath, picg_bool isDynamic) {
    /*
        Load OBJ and MTL
    */
    picg_mesh* modelmesh = picg_meshObj_create(filepath);
    picg_material *modelmaterial = picg_material_create_loadFromFile(filepath);

    picg_physicsmodel* physicsmodel = (picg_physicsmodel*)calloc(sizeof(modelmesh) + sizeof(modelmaterial), 1);

    if(modelmesh == NULL) {
        PICG_ERROR("OBJ Model mesh failed to load");
        return NULL;
    }

    if(modelmaterial == NULL) {
        PICG_ERROR("OBJ Model MTL (material) failed to load");
    }

    /*
        Load physics
    */

    picg_physics_physicsComponent* physics = picg_physics_physicsComponent_create(isDynamic);
    picg_physics_physicsComponent_calculateAABB(&physics->aabb, modelmesh);

    physicsmodel->mesh = modelmesh;
    physicsmodel->material = modelmaterial;
    physicsmodel->physics = physics;

    return physicsmodel;
}