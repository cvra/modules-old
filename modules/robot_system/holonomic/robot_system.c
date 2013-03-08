#include <holonomic/robot_system.h>
#include <math.h>
#include <aversive/error.h>

#define DEG(x) ((x) * (180.0 / M_PI))
#define RAD(x) ((x) * (M_PI / 180.0))

void rsh_init(struct robot_system_holonomic *rs) {
    rs->betas[0] = RAD(60); 
    rs->betas[1] = RAD(180); 
    rs->betas[2] = RAD(300); 

    /** @todo Change default wheel radius. */
    rs->wheel_radius[0] = 10.;
    rs->wheel_radius[1] = 10.;
    rs->wheel_radius[2] = 10.;

    /** @todo Change default wheel distance. */
    rs->wheel_distance[0] = 100.;
    rs->wheel_distance[1] = 100.;
    rs->wheel_distance[2] = 100.;

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
    /** @todo grab the robot angle from position manager. */
    /** @todo add real physical parameters. */
    float theta_r = 0.;
    float omega_r;
    float omega_t;
    int i;

    for(i=0;i<3;i++) {
        omega_r = rs->speed / rs->wheel_radius[i] * 
                     cos(theta_r - rs->direction + rs->betas[i] - M_PI / 2);
        omega_t = - rs->rotation_speed * rs->wheel_distance[i] / rs->wheel_radius[i];

        /* TODO cs_set_consign((omega_r+omega_t)*steps_per_imp_per_rad_per_second) */
        DEBUG(E_ROBOT_SYSTEM, "wheel %d : omega_t=%.1f omega_r=%.1f", i, omega_t, omega_r);

    }
}
