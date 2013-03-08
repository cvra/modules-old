#include <holonomic/robot_system.h>
#include <math.h>
#include <aversive/error.h>

#define DEG(x) ((x) * (180.0 / M_PI))
#define RAD(x) ((x) * (M_PI / 180.0))

void rsh_init(struct robot_system_holonomic *rs) {

    rs->geometry = NULL;
    rs->motors[0] = NULL;
    rs->motors[1] = NULL;
    rs->motors[2] = NULL;
    rs->speed = 0.;
    rs->rotation_speed = 0.;
    rs->direction = 0.;
}

void rsh_set_cs(struct robot_system_holonomic *rs, int index, struct cs *cs) {
    rs->motors[index] = cs;
} 


void rsh_set_direction(struct robot_system_holonomic *rs, float theta_v) {
    /** @todo should we do a modulo pi here ? */
    rs->direction = theta_v;
}

void rsh_set_speed(struct robot_system_holonomic *rs, int speed) {
    rs->speed = speed;
}

void rsh_set_rotation_speed(struct robot_system_holonomic *rs, int omega_r) {
    rs->rotation_speed = omega_r;
}

void rsh_update(struct robot_system_holonomic *rs) {
    if(rs->geometry == NULL)
        return;

    /** @todo grab the robot angle from position manager. */
    /** @todo add real physical parameters. */
    float theta_r = 0.;
    float omega_r;
    float omega_t;
    int i;

    for(i=0; i<3; i++) {
        omega_r = rs->speed / rs->geometry->wheel_radius[i] * 
                     cos(theta_r - rs->direction + rs->geometry->betas[i] - M_PI / 2);
        omega_t = - rs->rotation_speed * rs->geometry->wheel_distance[i] / rs->geometry->wheel_radius[i];

        /* TODO cs_set_consign((omega_r+omega_t)*steps_per_imp_per_rad_per_second) */
        DEBUG(E_ROBOT_SYSTEM, "wheel %d : omega_t=%.1f omega_r=%.1f", i, omega_t, omega_r);
    }
}


void rsh_set_base_geometry(struct robot_system_holonomic *rs, struct holonomic_base_geometry *geometry) {
    rs->geometry = geometry;
}
