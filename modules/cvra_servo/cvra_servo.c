#include <cvra_servo.h>

void cvra_servo_set(void *base, int channel, int32_t value) {
    if(channel < 0 || channel > 3)
        return;

    IOWR(base, channel, value);
}
