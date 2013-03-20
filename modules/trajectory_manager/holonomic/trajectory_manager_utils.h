#ifndef _TRAJECTORY_MANAGER_UTILS_HOLONOMIC_H_
#define _TRAJECTORY_MANAGER_UTILS_HOLONOMIC_H_

/** @todo : check les inludes et faire les comment
 * Faire les bons nom de foncti ons*/
#include <aversive.h>
#include <aversive/error.h>
#include <holonomic/robot_system.h>
#include <holonomic/trajectory_manager.h>
#include <vect2.h>

/* Event's period */
#define TRAJ_EVT_PERIOD (25000UL/SCHEDULER_UNIT) /** < 25 ms */

/* Event that set a consign for robot_system depending on the trajectory */
void holonomic_trajectory_manager_event(void * param);

/* True if the robot is within the distance d_win of the trajectory's target */
uint8_t holonomic_robot_in_xy_window(struct h_trajectory *traj, double d_win);

/* Same thing for the angle */
uint8_t holonomic_robot_in_angle_window(struct h_trajectory *traj, double a_win_rad);

/* Delete a trajectory event */
void holonomic_delete_event(struct h_trajectory *traj);

/* Schedules a trajectory event */
void holonomic_schedule_event(struct h_trajectory *traj);

#endif

