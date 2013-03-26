#ifndef _ROBOT_POSITION_MANAGER_H_
#define _ROBOT_POSITION_MANAGER_H_

#include <math.h>
#include <vect2.h>
#include <aversive.h>


/**@brief Defines the geometry of a single holonomic base. */
struct holonomic_base_geometry {
    /** Angle of the wheels relative to the robot (\f$\beta_i\f$) */
    float beta[3];
    float cos_beta[3];  /**< Cosine of the betas */
    float sin_beta[3];  /**< Sine of the betas */

    /** Radius of the robot wheels (\f$r_i\f$). */
    float wheel_radius[3];

    /** Distance of the wheel to the center of the robot (\f$D_i\f$). */
    float wheel_distance[3];

    /** Steps per full rotation */
    int32_t encoder_resolution;
};


/** @brief Stores a cartesian position in double.
 *
 * This structure holds a position of the robot in the double precision format.
 * @sa xya_position_s16
 */
struct holonomic_xya_position {
    double x; /**< The X coordinate, in mm. */
    double y; /**< The Y coordinate, in mm. */
    double a; /**< The angle relative to the X axis, in radians. */
};

/**@brief Stores a cartesian position in int.
 * 
 * Same as xya_position but in integers.
 * @note The angle is stocked in degrees.
 * @sa xya_position
 */
struct holonomic_xya_position_s16 {
    int16_t x; /**< The X coordinate, in mm. */
    int16_t y; /**< The Y coordinate, in mm. */
    int16_t a; /**< The angle relative to the X axis in degrees. */
};

/** \brief Instance of the odometry subsystem.
 *
 * This structure holds everything that is needed to compute and store the
 * position of the robot.
 */
struct holonomic_robot_position {
    struct holonomic_base_geometry geometry;    /**< The physical parameters of the robot. */
    struct holonomic_xya_position pos_d;                  /**< Position of the robot in double. */
    struct holonomic_xya_position previous_pos_d;         /**< The previous position of the robot */

    struct holonomic_xya_position_s16 pos_s16;            /**< Position of the robot in integers. */

    int32_t (*motor_encoder[3])(void *);        /**< Callback functions for motor encoders */
    void* motor_encoder_param[3];               /**< Callback function parameters */

    int32_t encoder_val[3];                     /**< Array of the values from the encoders */
    float update_frequency;                     /**< Frequency at which position_manage is called */
};


/** @brief Initialization of the odometry subsystem.
 *
 * This function initialize a robot_position structure, setting everything to 0.
 * @param [in] pos The odometry instance to initialize. 
 */
void holonomic_position_init(struct holonomic_robot_position *pos);


/** @brief Set a new robot position.
 * @param [in] pos The odometry instance.
 * @param [in] x, y The new coordinate of the robot, in mm.
 * @param [in] a_deg The new angle of the robot, in degree.
 */
void holonomic_position_set(struct holonomic_robot_position *pos, int16_t x, int16_t y, double a_deg);


/** @brief Sets the physical parameters of the robot's base. 
 * @param [in] pos The robot_position instance to configure.
 * @param [in] beta Array[3] of the angles of the wheels' orientations to the robot.
 * @param [in] wheel_radius Array[3] of the wheels' radii.
 * @param [in] wheel_distance Array[3] of the wheels' distances to the robot's center.
 * @param [in] encoder_resolution Encoder step per revolution of a wheel.
 */
void holonomic_position_set_physical_params(struct holonomic_robot_position *pos, float beta[static 3],
                  float wheel_radius[static 3], float wheel_distance[static 3], int32_t encoder_resolution);

/** @brief Sets the frequency at which the function position_manage is called
 * @param [in] pos The robot_position instance to configure.
 * @param [in] frequency New frequency.
 */
void holonomic_position_set_update_frequency(struct holonomic_robot_position *pos, float frequency);

/** @brief Returns the instant translation speed of the robot.
 * @param [in] pos The robot_position instance.
 * @return Translation speed in mm/s
 */
double holonomic_position_get_instant_translation_speed(struct holonomic_robot_position *pos);

/** @brief Returns the instant rotation speed of the robot.
 * @param [in] pos The robot_position instance.
 * @return Rotation speed in rad/s
 */
double holonomic_position_get_instant_rotation_speed(struct holonomic_robot_position *pos);

/** @brief Returns the instant translation speed of the robot in int32_t.
 * @param [in] pos The robot_position instance.
 * @return Translation speed in mm/s
 */
int32_t holonomic_position_get_translation_speed_int(void *data);

/** @brief Returns the instant rotation speed of the robot in int32_t.
 * @param [in] pos The robot_position instance.
 * @return Rotation speed in rad/s
 */
int32_t holonomic_position_get_rotation_speed_int(void * data);

/** @brief Define callback function for motor encoders.
 *
 * @param [in] pos The robot_position instance.
 * @param [in] *motor_encoder[] A array of 3 callback functions. TODO: force the length to 3
 * @param [in] motor_encoder_param Array of the 3 parameters for the callback functions. 
 */
void holonomic_position_set_mot_encoder(struct holonomic_robot_position *pos,
                                        int32_t (*motor_encoder[static 3])(void *),
                                        void *motor_encoder_param[static 3]);

/** @brief Updates the position.
 *
 * @param [in] pos The odometry system instance.
 *
 * @note This function should be called at a fixed interval to ensure good
 * results.
 */
void holonomic_position_manage(struct holonomic_robot_position *pos);


/** @brief Get current X. 
 *
 * @param [in] pos The odometry system instance.
 * @return Current x in mm in integer.
 */ 
int16_t holonomic_position_get_x_s16(struct holonomic_robot_position *pos);

/** @brief Get current Y. 
 *
 * @param [in] pos The odometry system instance.
 * @return Current Y in mm in integer.
 */
int16_t holonomic_position_get_y_s16(struct holonomic_robot_position *pos);

/** @brief Get current angle. 
 *
 * @param [in] pos The odometry system instance.
 * @return Current angle in degrees in integer.
 */
int16_t holonomic_position_get_a_deg_s16(struct holonomic_robot_position *pos);


/** @brief Get current angle. Can be used with the cs_manager
 *
 * @param [in] pos The odometry system instance.
 * @return Current angle in degrees in integer.
 */
int32_t holonomic_position_get_a_deg_s32(void *data);

/** @brief Get current X. 
 *
 * @param [in] pos The odometry system instance.
 * @return Current x in mm in double.
 */ 
double holonomic_position_get_x_double(struct holonomic_robot_position *pos);

/** @brief Get current X. 
 *
 * @param [in] pos The odometry system instance.
 * @return Current x in mm in float.
 */ 
float holonomic_position_get_x_float(struct holonomic_robot_position *pos);

/** @brief Get current Y. 
 *
 * @param [in] pos The odometry system instance.
 * @return Current Y in mm in double.
 */ 
double holonomic_position_get_y_double(struct holonomic_robot_position *pos);

/** @brief Get current Y. 
 *
 * @param [in] pos The odometry system instance.
 * @return Current Y in mm in float.
 */ 
float holonomic_position_get_y_float(struct holonomic_robot_position *pos);

/** @brief Get current position
 * 
 * @param [in] pos The odometry system instance.
 * @returns current position stored in a vect2_cart.
 */
vect2_cart holonomic_position_get_xy_vect(struct holonomic_robot_position *pos);

/** @brief Returns current angle.
 *
 * @param [in] pos The odometry system instance.
 * @returns Current angle in radians in double.
 */
double holonomic_position_get_a_rad_double(struct holonomic_robot_position *pos);

/** @brief Returns current angle.
 *
 * @param [in] pos The odometry system instance.
 * @returns Current angle in radians in float.
 */
float holonomic_position_get_a_rad_float(struct holonomic_robot_position *pos);

/** @} */

#endif
