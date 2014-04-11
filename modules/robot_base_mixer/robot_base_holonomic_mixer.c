
#include <stdbool.h>
#include <math.h>

#include "robot_base_mixer.h"

// TODO wrong constants, replace by dimensions from CAD/calibration

// wheel angle (from robot x axis to wheel rotation axis)
static const float beta[3] = {
    0,                        //   0 deg
    2.0943951023931954923084, // 120 deg
    4.1887902047863909846168  // 240 deg
};

// wheel radius
static const float r[3] = {
    0.01855,
    0.01855,
    0.01855
};

// wheel distance from center
static const float D[3] = {
    0.095,  // inner 87.7 mm outer 100 mm = 0.09385 (0.095 measured!?)
    0.095,
    0.095
};


// conversion matrices
static float rtw[3][3];
static float wtr[3][3];

static void compute_matrix(void)
{
    static bool done = false;
    if (done)
        return;
    // robot to wheel matrix
    rtw[0][0] = -D[0];
    rtw[1][0] = -D[1];
    rtw[2][0] = -D[2];
    rtw[0][1] = sin(beta[0]);
    rtw[1][1] = sin(beta[1]);
    rtw[2][1] = sin(beta[2]);
    rtw[0][2] = -cos(beta[0]);
    rtw[1][2] = -cos(beta[1]);
    rtw[2][2] = -cos(beta[2]);
    // wheel to robot matrix
    float c = 1 / (  D[0] * sin(beta[1] - beta[2])
                   - D[1] * sin(beta[0] - beta[2])
                   + D[2] * sin(beta[0] - beta[1]) );
    wtr[0][0] = c * sin(beta[2] - beta[1]);
    wtr[0][1] = c * sin(beta[0] - beta[2]);
    wtr[0][2] = c * sin(beta[1] - beta[0]);
    wtr[1][0] = c * (D[2]*cos(beta[1]) - D[1]*cos(beta[2]));
    wtr[1][1] = c * (D[0]*cos(beta[2]) - D[2]*cos(beta[0]));
    wtr[1][2] = c * (D[1]*cos(beta[0]) - D[0]*cos(beta[1]));
    wtr[2][0] = c * (D[2]*sin(beta[1]) - D[1]*sin(beta[2]));
    wtr[2][1] = c * (D[0]*sin(beta[2]) - D[2]*sin(beta[0]));
    wtr[2][2] = c * (D[1]*sin(beta[0]) - D[0]*sin(beta[1]));
    done = true;
}

void holonomic_base_mixer_robot_to_wheels(float dx, float dy, float dtheta,
    float dwheels[3])
{
    compute_matrix();
    float rdwheel[3];
    rdwheel[0] = dtheta * rtw[0][0] + dx * rtw[0][1] + dy * rtw[0][2];
    rdwheel[1] = dtheta * rtw[1][0] + dx * rtw[1][1] + dy * rtw[1][2];
    rdwheel[2] = dtheta * rtw[2][0] + dx * rtw[2][1] + dy * rtw[2][2];
    dwheels[0] = rdwheel[0]/r[0];
    dwheels[1] = rdwheel[1]/r[1];
    dwheels[2] = rdwheel[2]/r[2];
}

void holonomic_base_mixer_wheels_to_robot(const float dwheels[3], float *dx,
    float *dy, float *dtheta)
{
    compute_matrix();
    float rdwheel[3] = {dwheels[0] * r[0],
                        dwheels[1] * r[1],
                        dwheels[2] * r[2]};
    *dtheta = rdwheel[0] * wtr[0][0]
            + rdwheel[1] * wtr[0][1]
            + rdwheel[2] * wtr[0][2];
    *dx     = rdwheel[0] * wtr[1][0]
            + rdwheel[1] * wtr[1][1]
            + rdwheel[2] * wtr[1][2];
    *dy     = rdwheel[0] * wtr[2][0]
            + rdwheel[1] * wtr[2][1]
            + rdwheel[2] * wtr[2][2];
}
