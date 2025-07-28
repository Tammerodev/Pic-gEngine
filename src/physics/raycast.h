#pragma once
#include "physicsComponent.h"
#include "../math/vector3D.h"

typedef struct {
    int NComponent;
    picg_vec3F collision_position;
} picg_physics_raycast_return;

picg_physics_raycast_return picg_physics_raycast_cast(picg_vec3F start, picg_vec3F direction, int max_distance, picg_physics_physicsComponent** worldcomponents, int NComponents, float resolution) {
    // Normalize the direction vector
    const float direction_mag = picg_vec3F_magnitude(&direction);

    const float normalized_direction_x = direction.x / direction_mag;
    const float normalized_direction_y = direction.y / direction_mag;
    const float normalized_direction_z = direction.z / direction_mag;

    // Store the ray's position
    picg_vec3F position_now = start;

    int iterations = 0;

    while(iterations < max_distance) {
        // Move the ray in the (normalized) direction
        position_now.x = position_now.x + normalized_direction_x * resolution;
        position_now.y = position_now.y + normalized_direction_y * resolution;
        position_now.z = position_now.z + normalized_direction_z * resolution;

        iterations++;

        // debug render
        picg_graphics_debug_ray_render(start.x, start.y, start.z, position_now.x, position_now.y, position_now.z);

        // collision check
        if(worldcomponents && NComponents) {
            for(int n = 0; n < NComponents; n++) {
                if(picg_physics_physicsComponent_isPointWithinAABB(&position_now, worldcomponents[n])) {
                    picg_physics_raycast_return ret_;

                    ret_.collision_position = position_now;
                    ret_.NComponent = n;

                    return ret_;
                }
            }
        }
    }


    picg_physics_raycast_return ret_;

    ret_.collision_position = position_now;
    ret_.NComponent = -1;

    return ret_;
}   