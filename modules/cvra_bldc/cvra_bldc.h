#ifndef _CVRA_BLDC_H_
#define _CVRA_BLDC_H_

#include <aversive.h>

/** Resets the device by setting all registers to 0. */
void cvra_bldc_reset(void * device);

/** Sets the PWM. */
void cvra_bldc_set_pwm(void * device, int32_t value);

void cvra_bldc_set_pwm_negative(void *device, int32_t value);

/** Gets encoder. */
int32_t cvra_bldc_get_encoder(void * device);

/** Sets encoder. */
void cvra_bldc_set_encoder(void * device, int32_t v);

#endif
