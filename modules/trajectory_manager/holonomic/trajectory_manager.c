#include <holonomic/trajectory_manager.h>
#include <holonomic/trajectory_manager_utils.h>

void trajectoryh_moving_straight_goto_xy_abs(struct h_trajectory *traj, double x_abs_mm, double y_abs_mm) {
    DEBUG(E_TRAJECTORY, "Go straight to XY");
    traj->moving_state = MOVING_STRAIGHT;
    /** Pour le warning unused_variable (nomalement seter la target */
    x_abs_mm = y_abs_mm;
    y_abs_mm = x_abs_mm;
    
    //htrajectory_manager_event(traj);
    holonomic_schedule_event(traj);
}
