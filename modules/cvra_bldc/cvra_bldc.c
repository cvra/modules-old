#include <aversive.h>
#include <cvra_bldc.h>

/** Resets the device by setting all registers to 0. */
void cvra_bldc_reset(cvra_bldc device) {
    IOWR(device, BLDC_CNT_REGISTER_OFFSET, 0);
    IOWR(device, BLDC_PMW_REGISTER_OFFSET, BLDC_PWM_MINIMAL_VALUE);
}

/** Sets the PWM. */
void cvra_bldc_set_pwm_0(cvra_bldc device, int32_t value) {
    if(value < BLDC_PWM_MINIMAL_VALUE && value > -BLDC_PWM_MINIMAL_VALUE)
        value = BLDC_PWM_MINIMAL_VALUE;

    IOWR(device, BLDC_PMW_REGISTER_OFFSET, value);
}

/** Gets encoder. */
int32_t cvra_bldc_get_encoder(cvra_bldc device) {
    volatile int32_t tmp;
    tmp = IORD(device, BLDC_CNT_REGISTER_OFFSET);
    return t;
}
