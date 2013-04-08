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
 * The module output to robot_system the speed, the angle of the speed
 * and the angular speed of the robot
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
    MOVING_IDLE,
};
/* Turning trajectories */
enum h_trajectory_turning_state {
    TURNING_CAP,
    TURNING_SPEEDOFFSET,
    TURNING_FACEPOINT,
    TURNING_IDLE,
};

/** A complete instance of the trajectory manager. */
struct h_trajectory {
    enum h_trajectory_moving_state moving_state;
    enum h_trajectory_turning_state turning_state;
    
                  
    vect2_cart xy_target; /**< Target for the moving part */
    double a_target;      /**< Target for the turning part */
    
    vect2_cart circle_centre; /**< Center of the circle for MOVING_CIRCLE */
    double arc_angle;         /**< For MOVING_CIRCLE : PI/2 -> a quarter of a cirlce  */
    vect2_cart point2face;    /**< Point to face for TURNING_FACEPOINT */
    
    /** Windows for the end of the trajectory, in distance and angular distance */
    double d_windows;
    double a_windows;
    
    /** Output to robot_system @todo : leur init à 0 
     * NOT USED YET*/
    double speed;
    double direction;
    double omega;
    
    /** Windows for arrival */
    double d_win;
    double a_win;
    
    /** Position of the robot */
    struct holonomic_robot_position *position;
    
    /** Binded robot system */
    struct robot_system_holonomic *robot;
    
    /** Associated controls systems */
    struct cs *csm_angle;
    struct cs *csm_speed;
    struct cs *csm_omega;
    
    double cs_hz;   /**< The frequency of the control system associated with this manager. */

    int8_t scheduler_task;    /**<< id of current task (-1 if no running task) */
};

/** @brief Structure initialization.
 *
 * @param [in] traj The trajectory manager to initialize.
 * @param [in] cs_hz The frequency of the control systems, in Hz. */
void holonomic_trajectory_init(struct h_trajectory *traj, double cs_hz);

/** @brief Sets the control systems.
 *
 * This function tells the trajectory manager which control system to use for
 * angle/speed/omega(andgular speed) control.
 *
 * @param [in] traj The trajectory manager instance.
 * @param [in] cs_s, cs_a, cs_o The control systems to use.
 */
void holonomic_trajectory_set_cs(struct h_trajectory *traj, struct cs *cs_a,
               struct cs *cs_s, struct cs *cs_o);
               
/** @brief Sets related robot params.
 *
 * Sets the robot_pos and robot_system used for the computation of the trajectory.
 * @param [in] traj The trajectory manager instance.
 * @param [in] rs   The related robot system.
 * @param [in] pos  The position manager instance of the robot. 
 */
void holonomic_trajectory_set_robot_params(struct h_trajectory *traj,
                 struct robot_system_holonomic *rs,
                 struct holonomic_robot_position *pos);
                 
/** @brief Manually set the consign.
 *
 * @param [in] traj The trajectory manager instance.
 * @param [in] speed The speed consign @todo : units
 * @param [in] direction The direction consign @todo : units
 * @param [in] omega The angular speed consign @todo : units
 */
void holonomic_trajectory_set_var(struct h_trajectory *traj, double speed, double direction, double omega);
                 
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

/** True if the robot is within the distance d_win of the trajectory's target */
uint8_t holonomic_robot_in_xy_window(struct h_trajectory *traj, double d_win);

#endif

