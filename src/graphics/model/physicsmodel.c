#include "physicsmodel.h"

void picg_physicsmodel_render(picg_physicsmodel* model) 
{
    picg_material_bind(model->material);

    picg_mesh_render(model->mesh);

    picg_material_unbind(model->material);

#if PICG_DEBUG
    if(g_runtime_debug) {
        picg_physics_physicsComponent_debug_render(model->physics, false);
    }
#endif
}

void picg_physicsmodel_update(picg_physicsmodel* physicsmodel) {
    picg_physics_physicsComponent_update(physicsmodel->physics, physicsmodel->mesh);
}