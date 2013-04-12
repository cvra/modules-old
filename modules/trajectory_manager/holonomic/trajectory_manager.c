#include <string.h>
#include <holonomic/trajectory_manager.h>
#include <holonomic/trajectory_manager_utils.h>
#include <holonomic/position_manager.h>

/** @todo : deux movement em même temps */

void holonomic_trajectory_moving_straight_goto_xy_abs(struct h_trajectory *traj, double x_abs_mm, double y_abs_mm) {
    DEBUG(E_TRAJECTORY, "Go straight to XY");
    traj->moving_state = MOVING_STRAIGHT;
    traj->turning_state = TURNING_IDLE;

    traj->xy_target.x = x_abs_mm;
    traj->xy_target.y = y_abs_mm;
    
    holonomic_trajectory_manager_event(traj);
    holonomic_schedule_event(traj);
}

void holonomic_trajectory_moving_circle(struct h_trajectory *traj, double x_center_abs, double y_center_abs, double arc_angle) {
    DEBUG(E_TRAJECTORY, "Make a nice circle");
    traj->moving_state = MOVING_CIRCLE;

    traj->circle_center.x = x_center_abs;
    traj->circle_center.y = y_center_abs;
    
    /** end of the circle */
    vect2_cart vec_to_center = {.x = traj->circle_center.x - holonomic_position_get_x_double(traj->position),
                                .y = traj->circle_center.y - holonomic_position_get_y_double(traj->position)};
    double radius = vect2_norm_cart(&vec_to_center);
    traj->radius = radius;
    
    traj->xy_target.x = x_center_abs + cos(atan2f(holonomic_position_get_y_double(traj->position) - y_center_abs, 
    holonomic_position_get_x_double(traj->position) - x_center_abs)-arc_angle)*radius;
    traj->xy_target.y = y_center_abs + sin(atan2f(holonomic_position_get_y_double(traj->position) - y_center_abs, 
    holonomic_position_get_x_double(traj->position) - x_center_abs)-arc_angle)*radius;
    
    holonomic_trajectory_manager_event(traj);
    holonomic_schedule_event(traj);
}

 void holonomic_trajectory_turning_cap(struct h_trajectory *traj, double cap)
 {
    DEBUG(E_TRAJECTORY, "Going to a cap");
    traj->moving_state = MOVING_IDLE;
    traj->turning_state = TURNING_CAP;
    
    traj->a_target = cap;
    
    holonomic_trajectory_manager_event(traj);
    holonomic_schedule_event(traj);
 }

void holonomic_trajectory_init(struct h_trajectory *traj, double cs_hz)
{
    memset(traj, 0, sizeof(struct h_trajectory));
    traj->cs_hz = cs_hz;
    traj->moving_state = MOVING_IDLE;
    traj->turning_state = TURNING_IDLE;
    traj->scheduler_task = -1;
}

void holonomic_trajectory_set_ramps(struct h_trajectory *traj, struct ramp_filter *speed_r,
               struct quadramp_filter *angle_qr, struct ramp_filter *omega_r)
{
    traj->speed_r = speed_r;
    traj->angle_qr = angle_qr;
    traj->omega_r = omega_r;
}

void holonomic_trajectory_set_robot_params(struct h_trajectory *traj,
                 struct robot_system_holonomic *rs,
                 struct holonomic_robot_position *pos)
{
    traj->robot = rs;
    traj->position = pos;
}

void holonomic_trajectory_set_windows(struct h_trajectory *traj,
                 double d_win, double a_win)
{
    traj->d_win = d_win;
    traj->a_win = a_win;
}

void holonomic_trajectory_set_var(struct h_trajectory *traj, int32_t speed, int32_t direction, int32_t omega)
{
    set_consigns_to_rsh(traj, speed, direction, omega);
}
