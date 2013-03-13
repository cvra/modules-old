

#ifndef _ROBOT_POSITION_MANAGER_H_
#define _ROBOT_POSITION_MANAGER_H_

#include <math.h>
#include <vect2.h>

#define CONFIG_MODULE_COMPENSATE_CENTRIFUGAL_FORCE

/**@brief Defines the geometry of a single holonomic base. */
struct holonomic_base_geometry {
    /** Angle of the wheels relative to the robot (\f$\beta_i\f$) */
    float beta[3];

    /** Radius of the robot wheels (\f$r_i\f$). */
    float wheel_radius[3];

    /** Distance of the wheel to the center of the robot (\f$D_i\f$). */
    float wheel_distance[3];
};


/** @brief Stores a cartesian position in double.
 *
 * This structure holds a position of the robot in the double precision format.
 * @sa xya_position_s16
 */
struct xya_position {
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
struct xya_position_s16 {
	int16_t x; /**< The X coordinate, in mm. */
	int16_t y; /**< The Y coordinate, in mm. */
	int16_t a; /**< The angle relative to the X axis in degrees. */
};

/** \brief Instance of the odometry subsystem.
 *
 * This structure holds everything that is needed to compute and store the
 * position of the robot.
 */
struct robot_position {
	struct holonomic_base_geometry;	        /**< The physical parameters of the robot. */
	struct xya_position pos_d;			    /**< Position of the robot in double. */
	struct xya_position_s16 pos_s16;	    /**< Position of the robot in integers. */
	struct rs_polar prev_encoders;		    /**< Previous state of the encoders. */

	int32_t (*motor_encoder[3])(void *);    /**< Callback functions for motor encoders */
    void* motor_encoder_param[3];           /**< Callback function parameters */
	
#ifdef CONFIG_MODULE_COMPENSATE_CENTRIFUGAL_FORCE	
	double centrifugal_coef;			    /**< Coefficient for the centrifugal computation */
#endif
};


/** @brief Initialization of the odometry subsystem.
 *
 * This function initialize a robot_position structure, setting everything to 0.
 * @param [in] pos The odometry instance to initialize. 
 */
void position_init(struct robot_position *pos);

#ifdef CONFIG_MODULE_COMPENSATE_CENTRIFUGAL_FORCE	
/** @brief Set centrifugal coef.
 * 
 * This functions sets the centrifugal coef for the odometry compensation.
 * @param [in] pos The odometry instance.
 * @param [in] coef The centrifugal force coefficient.
 * @sa CONFIG_MODULE_COMPENSATE_CENTRIFUGAL_FORCE
 */
void position_set_centrifugal_coef(struct robot_position *pos, double coef);
#endif

/** @brief Set a new robot position.
 * @param [in] pos The odometry instance.
 * @param [in] x, y The new coordinate of the robot, in mm.
 * @param [in] a_deg The new angle of the robot, in degree.
 */
void position_set(struct robot_position *pos, int16_t x, int16_t y, double a_deg);


/** @brief Sets the physical parameters of the robot's base. 
 * @param [in] pos The robot_position instance to configure.
 * @param [in] beta Array[3] of the angles of the wheels' orientations to the robot.
 * @param [in] wheel_radius Array[3] of the wheels' radii.
 * @param [in] wheel_distance Array[3] of the wheels' distances to the robot's center.
 */
void position_set_base_geometry(struct robot_position *pos, float* beta,
				  float* wheel_radius, float* wheel_distance);


/** @brief Define callback function for motor encoders.
 *
 * @param [in] pos The robot_position instance.
 * @param [in] *motor_encoder[] A array of 3 callback functions. TODO: force the length to 3
 * @param [in] motor_encoder_param Array of the 3 parameters for the callback functions. 
 */
void holonomic_position_set_mot_encoder(struct robot_position *pos,
                                        int32_t (*motor_encoder[])(void *),
                                        void *motor_encoder_param[]);

/** @brief Updates the position.
 *
 * @param [in] pos The odometry system instance.
 *
 * @note This function should be called at a fixed interval to ensure good
 * results.
 */
void position_manage(struct robot_position *pos);


/** @brief Get current X. 
 *
 * @param [in] pos The odometry system instance.
 * @return Current x in mm in integer.
 */ 
int16_t position_get_x_s16(struct robot_position *pos);

/** @brief Get current Y. 
 *
 * @param [in] pos The odometry system instance.
 * @return Current Y in mm in integer.
 */
int16_t position_get_y_s16(struct robot_position *pos);

/** @brief Get current angle. 
 *
 * @param [in] pos The odometry system instance.
 * @return Current angle in degrees in integer.
 */
int16_t position_get_a_deg_s16(struct robot_position *pos);

/** @brief Get current X. 
 *
 * @param [in] pos The odometry system instance.
 * @return Current x in mm in double.
 */ 
double position_get_x_double(struct robot_position *pos);

/** @brief Get current X. 
 *
 * @param [in] pos The odometry system instance.
 * @return Current x in mm in float.
 */ 
float position_get_x_float(struct robot_position *pos);

/** @brief Get current Y. 
 *
 * @param [in] pos The odometry system instance.
 * @return Current Y in mm in double.
 */ 
double position_get_y_double(struct robot_position *pos);

/** @brief Get current Y. 
 *
 * @param [in] pos The odometry system instance.
 * @return Current Y in mm in float.
 */ 
float position_get_y_float(struct robot_position *pos);

/** @brief Get current position
 * 
 * @param [in] pos The odometry system instance.
 * @returns current position stored in a vect2_cart.
 */
vect2_cart position_get_xy_vect(struct robot_position *pos);

/** @brief Returns current angle.
 *
 * @param [in] pos The odometry system instance.
 * @returns Current angle in radians in double.
 */
double position_get_a_rad_double(struct robot_position *pos);

/** @brief Returns current angle.
 *
 * @param [in] pos The odometry system instance.
 * @returns Current angle in radians in float.
 */
float position_get_a_rad_float(struct robot_position *pos);

/** @} */

#endif
