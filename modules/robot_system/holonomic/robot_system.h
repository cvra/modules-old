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

#ifndef _ROBOT_SYSTEM_HOLONOMIC_H_
#define _ROBOT_SYSTEM_HOLONOMIC_H_

/** Instance of a robot system for holonomic robots.
 * The units of speed and rotation speed must be in coders unit. */
struct robot_system_holonomic {
    /** Angle of the wheels relative to the robot (\f$\beta_i\f$) */
    float betas[3];

    /** Radius of the robot wheels (\f$r_i\f$). */
    float wheel_radius[3];

    /** Distance of the wheel to the center of the robot (\f$D_i\f$). */
    float wheel_distance[3];

    /** Speed consign of the robot (\f$V\f$), in coder units. */
    float speed;

    /** Direction to which the robot moves (\f$\theta_V\f$). 
     * @todo Is it between \f$-\pi\f$ and \f$\pi\f$ or between 0 and \f$2\pi\f$? Does it even change sth ?
     */
    float direction;

    /** Rotation speed of the robot (\f$\Omega\f$). 
     */
    float rotation_speed; 

    /** The 3 speed regulators which are connected on the motors. */
    struct cs* motors[3];
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

/** Sets the speed of the robot.
 * @param [in] rs The robot_system instance.
 * @param [in] speed The speed of the robot, in m/s.
 */
void rsh_set_speed(struct robot_system_holonomic *rs, int speed);

/** Sets the angular speed of the robot.
 * @param [in] rs The robot_system instance.
 * @param [in] omega_r The change in robot orientation, in rad / s.
 */
void rsh_set_rotation_speed(struct robot_system_holonomic *rs, int omega_r);

#endif
