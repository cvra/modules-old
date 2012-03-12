
#include <aversive.h>
#include <cvra_bldc.h>

/* Registers */
#define BLDC_MOTPOS_REGISTER_OFFSET 0x02
#define BLDC_PWM_REGISTER_OFFSET 0x01
#define BLDC_CNT_REGISTER_OFFSET 0x00

/* Constants */
#define BLDC_PWM_MINIMAL_VALUE 10


/** Resets the device by setting all registers to 0. */
void cvra_bldc_reset(void * device) {
    IOWR((int32_t *)device, BLDC_CNT_REGISTER_OFFSET, 0);
    IOWR((int32_t *)device, BLDC_PWM_REGISTER_OFFSET, BLDC_PWM_MINIMAL_VALUE);
    IOWR((int32_t *)device, BLDC_MOTPOS_REGISTER_OFFSET, 0);
}

/** Sets the PWM. */
void cvra_bldc_set_pwm(void * device, int32_t value) {
    if(value < BLDC_PWM_MINIMAL_VALUE && value > -BLDC_PWM_MINIMAL_VALUE)
        value = BLDC_PWM_MINIMAL_VALUE;

    if(value > 1000) value = 1000;
    if(value < -1000) value = -1000;

    IOWR((int32_t *)device, BLDC_PWM_REGISTER_OFFSET, value);
}

void cvra_bldc_set_pwm_negative(void *device, int32_t value) {
	cvra_bldc_set_pwm(device, -value);
}

/** Gets encoder. */
int32_t cvra_bldc_get_encoder(void * device) {
    volatile int32_t tmp;
    tmp = IORD((int32_t *)device, BLDC_CNT_REGISTER_OFFSET);
    return tmp;
}

/** Sets encoder. */
void cvra_bldc_set_encoder(void * device, int32_t v) {
    IOWR((int32_t *)device, BLDC_CNT_REGISTER_OFFSET, v);
}

/** Gets motor position. */
int32_t cvra_bldc_get_motpos(void * device) {
    volatile int32_t tmp;
    tmp = IORD((int32_t *)device, BLDC_MOTPOS_REGISTER_OFFSET);
    return tmp;
}

/** Sets motor position. */
void cvra_bldc_set_motpos(void * device, int32_t v) {
    IOWR((int32_t *)device, BLDC_MOTPOS_REGISTER_OFFSET, v);
}
