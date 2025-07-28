#pragma once
#include <math.h>


typedef struct {
    float x, y, z;
} picg_vec3F;

typedef struct {
    int x, y, z;
} picg_vec3I;

// Calculate length of vector, we believe you wouldnt pass a null pointer?
const float picg_vec3F_magnitude(picg_vec3F* v);