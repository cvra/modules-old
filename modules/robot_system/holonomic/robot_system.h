/** @file modules/robot_system/holonomic/robot_system.h
 * @author CVRA
 * @brief Handles conversion from angles and speeds to motors and reverse.
 *
 * This modules receives the values for the speeds of the robot in the
 * angle and speed of the robot, and outputs the speeds of the wheels.
 *
 * The speeds of the robot are given using 1 angle, 1 angular speed and
 * 1 linear speed. 
 * - \f$\Theta_V\f$ is the angle between the movement direction of the
 *   robot and the X-axis.
 * - \f$\omega\f$ is the angular speed at which the robot turns onto itself
 *   (change in heading).
 * - \f$V$\f$ is the linear speed of the robot.
 *
 * This convention allows us to easily separate the forward cinematics from
 * the trajectory generation. 
 *
 * If you need more details about how it works, you can read doc/holonomic/cinematics.pdf
 */
#include <aversive.h>
#include <control_system_manager.h>
#include <holonomic/position_manager.h>

#ifndef _ROBOT_SYSTEM_HOLONOMIC_H_
#define _ROBOT_SYSTEM_HOLONOMIC_H_

/** Instance of a robot system for holonomic robots. */
struct robot_system_holonomic { 
    /** Speed consign of the robot (\f$V\f$), in coder units. */
    float speed;

    /** Direction to which the robot moves (\f$\theta_V\f$). 
     * @todo Is it between \f$-\pi\f$ and \f$\pi\f$ or between 0 and \f$2\pi\f$? Does it even change sth ?
     */
    float direction;

    /** Rotation speed of the robot (\f$\Omega\f$). */
    float rotation_speed; 

    /** The 3 speed regulators which are connected on the motors. */
    struct cs* motors[3];

    /** The geometry of the base. */
    struct holonomic_base_geometry *geometry;

};

/** Inits a robot_system struct.
 * @param [in, out] rs The instance to init.
 */
void rsh_init(struct robot_system_holonomic *rs);

/** This functions updates the PWMs based on the input values and the current
 * position of the robot.
 * @param [in] rs The robot_system instance to update.
 */
void rsh_update(struct robot_system_holonomic *rs);

/** Sets the speed regulator for a single axis.
 * @param [in] rs The robot_system instance.
 * @param [in] index The index (0, 1 or 2) of this axis.
 * @param [in] cs The control system for this axis.
 */
void rsh_set_cs(struct robot_system_holonomic *rs, int index, struct cs *cs); 

/** Sets the movement angle consign.
 * @param [in] rs The robot_system instance.
 * @param [in] theta_v The angle between the movement direction of the robot and 
 * the X-axis, in radians.
 */
void rsh_set_direction(struct robot_system_holonomic *rs, float theta_v);

/** Sets the movement angle consign, in int (necessary for control_system).
 * @param [in] rs The robot_system instance.
 * @param [in] theta_v The angle between the movement direction of the robot and 
 * the X-axis, in degree.
 */
void rsh_set_direction_int(void * data, int32_t theta_v_deg);

/** Sets the speed of the robot.
 * @param [in] rs The robot_system instance.
 * @param [in] speed The speed of the robot, in m/s.
 */
void rsh_set_speed(void *data, int32_t speed);

/** Sets the angular speed of the robot, compliant with the cs_manager require
 * @param [in] rs The robot_system instance.
 * @param [in] omega_r The change in robot orientation, in deg / s.
 */
void rsh_set_rotation_speed(void *data, int32_t omega_d);

/** Sets the geometry base.
 * @param [in, out] rs The robot_system instance.
 * @param [in] geometry The geometry of the base.
 */
void rsh_set_base_geometry(struct robot_system_holonomic *rs, struct holonomic_base_geometry *geometry);

#endif
