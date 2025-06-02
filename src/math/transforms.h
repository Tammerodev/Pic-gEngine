#pragma once
#include "vector3D.h"
#include <math.h>

#define DEG2RAD(deg) ((deg) * (3.14159 / 180.0f))


picg_vec3F picg_transform_rotate(const picg_vec3F position, const picg_vec3F rotation_deg) {
    // Degrees->radians, also flip rotation (just works that way)
    float rx = -rotation_deg.x * (3.14159f / 180.f);
    float ry = -rotation_deg.y * (3.14159f / 180.f);
    float rz = -rotation_deg.z * (3.14159f / 180.f);

    // Rotate around X axis
    picg_vec3F pos_x = {
        position.x,
        position.y * cos(rx) - position.z * sin(rx),
        position.y * sin(rx) + position.z * cos(rx)
    };

    // Rotate around Y axis
    picg_vec3F pos_y = {
        pos_x.x * cos(ry) + pos_x.z * sin(ry),
        pos_x.y,
        -pos_x.x * sin(ry) + pos_x.z * cos(ry)
    };

    // Rotate around Z axis
    picg_vec3F pos_z = {
        pos_y.x * cos(rz) - pos_y.y * sin(rz),
        pos_y.x * sin(rz) + pos_y.y * cos(rz),
        pos_y.z
    };

    return pos_z;
}
