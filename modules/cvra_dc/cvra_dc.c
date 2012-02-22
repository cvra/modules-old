#include <aversive.h>
#include <cvra_dc.h>

/** Resets the device by setting all registers to 0. */
void cvra_dc_reset(cvra_dc device) {
    IOWR(device, DC_CNT0_REGISTER_OFFSET, 0);
    IOWR(device, DC_CNT1_REGISTER_OFFSET, 0);
    IOWR(device, DC_PWM0_REGISTER_OFFSET, 0);
    IOWR(device, DC_PWM1_REGISTER_OFFSET, 0);
}

/** Sets the PWM 0. */
void cvra_dc_set_pwm_0(cvra_dc device, int32_t value) {
    if(value > DC_PWM_MAX_VALUE) value = DC_PWM_MAX_VALUE;
    if(value < -DC_PWM_MAX_VALUE)value = -DC_PWM_MAX_VALUE;
    IOWR(device, DC_PWM0_REGISTER_OFFSET, value);
}

/** Sets the PWM 1. */
void cvra_dc_set_pwm_1(cvra_dc device, int32_t value) {
    if(value > DC_PWM_MAX_VALUE) value = DC_PWM_MAX_VALUE;
    if(value < -DC_PWM_MAX_VALUE)value = -DC_PWM_MAX_VALUE;
    IOWR(device, DC_PWM1_REGISTER_OFFSET, value);
}

/** Gets encoder 0. */
int32_t cvra_dc_get_encoder_0(cvra_dc device) { 
    volatile int32_t tmp;
    tmp = IORD(device, DC_CNT0_REGISTER_OFFSET);
    return tmp;
}
    
void cvra_dc_set_encoder_0(cvra_dc device, const int32_t v) {
    IOWR(device, DC_CNT0_REGISTER_OFFSET, v);
}

/** Gets encoder 1. */
int32_t cvra_dc_get_encoder_1(cvra_dc device) {
    volatile int32_t tmp;
    tmp = IORD(device, DC_CNT1_REGISTER_OFFSET);
    return tmp;
}

void cvra_dc_set_encoder_1(cvra_dc device, const int32_t v) {
    IOWR(device, DC_CNT1_REGISTER_OFFSET, v);
}
