

#ifndef _CVRA_MOTOR_H_
#define _CVRA_MOTOR_H_

#include <aversive.h>

/**
 @brief Inits the CVRA motor control hardware peripheral.
 
 @param [in] base_adress The base adress of the peripheral on the Avalon bus.
 */
void cvra_motor_init(void *base_adress);

/**
 @brief Sets the PWM output of the controller.
 
 @param [in] base_adress The base adress of the peripheral on the Avalon bus.
 @param [int] value The value of the PWM on 16 bit.
 */
void cvra_motor_set_pwm(void *base_adress, int16_t value);

/**
 @brief Sets the encoder value of the controller.
 
 @param [in] base_adress The base adress of the peripheral on the Avalon bus.
 @param [int] value The value of the encoder on 32 bit.
 */
void cvra_motor_set_encoder(void *base_adress, int32_t value);

/**
 @brief Reads the value of the encoder.
 @param [in] base_adress The base adress of the peripheral on the Avalon bus.
 */
int32_t cvra_motor_get_encoder(void *base_adress);

/** The error number for this module. */
#define E_CVRA_MOTOR 10

#endif
