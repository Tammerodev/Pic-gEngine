#include "vector3D.h"

const float picg_vec3F_magnitude(picg_vec3F *v)
{
    return sqrtf((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
}