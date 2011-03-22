
#include <aversive.h>
#include <cvra_bldc.h>

/* Registers */
#define BLDC_PWM_REGISTER_OFFSET 0x00
#define BLDC_CNT_REGISTER_OFFSET 0x01

/* Constants */
#define BLDC_PWM_MINIMAL_VALUE 40


/** Resets the device by setting all registers to 0. */
void cvra_bldc_reset(void * device) {
    IOWR((int *)device, BLDC_CNT_REGISTER_OFFSET, 0);
    IOWR((int *)device, BLDC_PWM_REGISTER_OFFSET, BLDC_PWM_MINIMAL_VALUE);
}

/** Sets the PWM. */
void cvra_bldc_set_pwm(void * device, int32_t value) {
    if(value < BLDC_PWM_MINIMAL_VALUE && value > -BLDC_PWM_MINIMAL_VALUE)
        value = BLDC_PWM_MINIMAL_VALUE;

    IOWR((int32_t *)device, BLDC_PWM_REGISTER_OFFSET, value);
}

/** Gets encoder. */
int32_t cvra_bldc_get_encoder(void * device) {
    volatile int32_t tmp;
    tmp = IORD((int *)device, BLDC_CNT_REGISTER_OFFSET);
    return tmp;
}

/** Sets encoder. */
void cvra_bldc_set_encoder(void * device, int32_t v) {
    IOWR((int32_t *)device, BLDC_CNT_REGISTER_OFFSET, v);
}
