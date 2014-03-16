
/*
 * Mixing functions from robot coordinates to wheels and back
 *
 * These functions are used for position integration and to map controller
 * outputs to wheel-motors
 *
 */

#ifndef ROBOT_BASE_MIXER_H
#define ROBOT_BASE_MIXER_H

void holonomic_base_mixer_robot_to_wheels(float dx, float dy, float dtheta,
    float dwheels[3]);
void holonomic_base_mixer_wheels_to_robot(const float dwheels[3], float *dx,
    float *dy, float *dtheta);

// TODO use this module for differential robot?
// void differential_base_mixer_robot_to_wheels(float dx, float dtheta,
//     float dwheels[2]);
// void differential_base_mixer_wheels_to_robot(const float dwheels[2], float *dx,
//     float *dtheta);

#endif // ROBOT_BASE_MIXER_H
