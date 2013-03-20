/** @file modules/trajectory_manager/holonomic/trajectory_manager.h
 * @author CVRA
 * @brief High-level trajectory generation for an holonomic robot
 * 
 * A trajectory consist of two things : a moving part and a turning part
 * Avaible Moving Part :
 *  - A Straight line
 *  - An arc of circle
 * Avaible Turning Part :
 *  - Fixed cap
 *  - Face a point
 *  - Fixed offset from the speed vector of the robot
 * 
 * The module output to robot_system the speed, the angle and the angular speed
 * of the robot
 */
 

/** For me :
 * CIRCLE : la cible et le centre, a partir de la position initial
 * STRAIGHT : la cible final
 * 
 */

#ifndef _TRAJECTORY_MANAGER_HOLONOMIC_H_
#define _TRAJECTORY_MANAGER_HOLONOMIC_H_

#include <aversive.h>
#include <aversive/error.h>
#include <holonomic/robot_system.h>
#include <holonomic/position_manager.h>
#include <vect2.h>



/* Moving trajectories */
enum h_trajectory_moving_state {
    MOVING_STRAIGHT,
    MOVING_CIRCLE,
};
/* Turning trajectories */
enum h_trajectory_turning_state {
    TURNING_CAP,
    TURNING_SPEEDOFFSET,
    TURNING_FACEPOINT,
};

/** A complete instance of the trajectory manager. */
struct h_trajectory {
    enum h_trajectory_moving_state moving_state;
    enum h_trajectory_turning_state turning_state;
    
                  
    vect2_cart xy_target; /**< Target for the moving part */
    double a_target; /**< Target for the turning part */
    
    /** Windows for the end of the trajectory, in distance and angular distance */
    double d_windows;
    double a_windows;
    
    /** Output to robot_system @todo : leur init à 0*/
    double speed;
    double direction;
    double omega;
    
    /** Windows for arrival */
    double d_win;
    double a_win;
    
    /** Position of the robot */
    struct xya_position *position;
    
    double cs_hz;   /**< The frequency of the control system associated with this manager. */

    int8_t scheduler_task;    /**<< id of current task (-1 if no running task) */
};

/** @brief Go to a point.
 *
 * This function makes the holonomic robot go to a point. Once the function is called, the
 * trajectory manager schedules its own event in the scheduler to regulate on
 * the point. This event is automatically deleted once the point is reached.
 *
 * @param [in] traj The trajectory manager instance.
 * @param [in] x_abs_mm, y_abs_mm The coordinates of the point in mm.
 *
 * @note This moving command is mixed with the current turning command 
 */
void holonomic_trajectory_moving_straight_goto_xy_abs(struct h_trajectory *traj, double x_abs_mm, double y_abs_mm);

#endif

