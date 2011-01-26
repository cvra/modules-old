/* This file implements the software driver for the motor control module
 * of the CVRA. This modules contains both a PWM and a quadrature decoder.
 * It is controlled by the following registers :
 * PWM_REG : Contains the current value of the PWM (on Xbits).
 * ENCODER_REG : Contains the current value of the quadrature counter 
 * on 32 bits.
 */ 

#include <cvra_motor.h>
#include <aversive/error.h>

void cvra_motor_init(void *base_adress) {
    NOTICE(E_CVRA_MOTOR, "Init of cvra_motor at base addres %p", base_adress);
    
}

void cvra_motor_set_pwm(void *base_adress, int16_t value) {
    
    
}


void cvra_motor_set_encoder(void *base_adress, int32_t value) {
    
    
}


int32_t cvra_motor_get_encoder(void *base_adress) {
    
    return 0;
}

