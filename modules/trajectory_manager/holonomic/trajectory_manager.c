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
