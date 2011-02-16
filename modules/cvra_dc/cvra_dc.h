#ifndef _CVRA_DC_H_
#define _CVRA_DC_H_

#include <aversive.h>
#include <cvra_dc_regs.h>


typedef struct {
    (void *)base_adress;
    int32_t encoder_value[2];
} cvra_dc;

/** Resets the device by setting all registers to 0. */
void cvra_dc_reset(cvra_dc *device);

/** Manage the device (reads encoders). */
void cvra_dc_manage(cvra_dc *device);

/** Sets the PWM 0. */
void cvra_dc_set_pwm_0(cvra_dc *device, int32_t value);

/** Sets the PWM 1. */
void cvra_dc_set_pwm_1(cvra_dc *device, int32_t value);

/** Gets encoder 0. */
int32_t cvra_dc_get_encoder_0(cvra_dc *device);

/** Gets encoder 1. */
int32_t cvra_dc_get_encoder_1(cvra_dc *device);

#endif
