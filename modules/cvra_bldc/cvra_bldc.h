#ifndef _CVRA_BLDC_H_
#define _CVRA_BLDC_H_

#include <aversive.h>

/* Registers */
#define BLDC_PMW_REGISTER_OFFSET 0x00
#define BLDC_CNT_REGISTER_OFFSET 0x01

/* Constants */
#define BLDC_PWM_MINIMAL_VALUE 40

typedef (void *) cvra_bldc;

/** Resets the device by setting all registers to 0. */
void cvra_bldc_reset(cvra_bldc device);

/** Sets the PWM. */
void cvra_bldc_set_pwm_0(cvra_bldc device, int32_t value);

/** Gets encoder. */
int32_t cvra_bldc_get_encoder(cvra_bldc device);

#endif
