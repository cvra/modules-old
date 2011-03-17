#ifndef _CVRA_BLDC_H_
#define _CVRA_BLDC_H_

#include <aversive.h>

/* Registers */
#define BLDC_PWM_REGISTER_OFFSET 0x00
#define BLDC_CNT_REGISTER_OFFSET 0x01

/* Constants */
#define BLDC_PWM_MINIMAL_VALUE 40


/** Resets the device by setting all registers to 0. */
void cvra_bldc_reset(void * device);

/** Sets the PWM. */
void cvra_bldc_set_pwm(void * device, int32_t value);

/** Gets encoder. */
int32_t cvra_bldc_get_encoder(void * device);

#endif
