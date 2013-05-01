#include <cvra_servo.h>

void cvra_servo_set(void *base, int channel, uint32_t value) {
    if(channel < 0 || channel > 3)
        return;

    IOWR(base, channel, value);
}

void cvra_servo_set0(void *base, uint32_t value){
    cvra_servo_set(base, 0, value);
}

void cvra_servo_set1(void *base, uint32_t value){
    cvra_servo_set(base, 1, value);
}

void cvra_servo_set2(void *base, uint32_t value){
    cvra_servo_set(base, 2, value);
}
