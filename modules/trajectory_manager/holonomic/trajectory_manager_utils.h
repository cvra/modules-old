#ifndef _TRAJECTORY_MANAGER_UTILS_HOLONOMIC_H_
#define _TRAJECTORY_MANAGER_UTILS_HOLONOMIC_H_

/** @todo : check les inludes et faire les comment
 * Faire les bons nom de foncti ons*/
#include <aversive.h>
#include <aversive/error.h>
#include <holonomic/robot_system.h>
#include <holonomic/trajectory_manager.h>
#include <vect2.h>

/* Periond des evenements */
#define TRAJ_EVT_PERIOD (25000UL/SCHEDULER_UNIT) /** < 25 ms */

void holonomic_trajectory_manager_event(void * param);
uint8_t is_holonomic_robot_in_xy_window(struct h_trajectory *traj, double d_win);
uint8_t is_holonomic_robot_in_angle_window(struct h_trajectory *traj, double a_win_rad);
void delete_holonomic_event(struct h_trajectory *traj);
void holonomic_schedule_event_event(struct h_trajectory *traj);
uint8_t is_holonomic_robot_in_xy_window(struct h_trajectory *traj, double d_win);

#endif

