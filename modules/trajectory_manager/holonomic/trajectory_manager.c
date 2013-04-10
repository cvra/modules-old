#include <string.h>
#include <holonomic/trajectory_manager.h>
#include <holonomic/trajectory_manager_utils.h>

void holonomic_trajectory_moving_straight_goto_xy_abs(struct h_trajectory *traj, double x_abs_mm, double y_abs_mm) {
    DEBUG(E_TRAJECTORY, "Go straight to XY");
    traj->moving_state = MOVING_STRAIGHT;

    traj->xy_target.x = x_abs_mm;
    traj->xy_target.y = y_abs_mm;
    
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

void holonomic_trajectory_set_cs(struct h_trajectory *traj, struct cs *cs_a,
               struct cs *cs_s, struct cs *cs_o)
{
    traj->csm_omega = cs_o;
    traj->csm_angle = cs_a;
    traj->csm_speed = cs_s;
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

void holonomic_trajectory_set_var(struct h_trajectory *traj, double speed, double direction, double omega)
{
    cs_set_consign(traj->csm_angle,direction);
    cs_set_consign(traj->csm_speed,speed);
    cs_set_consign(traj->csm_omega,omega);
}
