#include "model.h"

void picg_model_render(picg_model* model) 
{
    picg_material_bind(model->material);

    picg_mesh_render(model->mesh);

    picg_material_unbind(model->material);
}