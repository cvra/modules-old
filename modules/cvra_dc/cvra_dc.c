#include <cvra_dc.h>

/** Registers definitions for the PWMs. */
static const int pwm_registers[] = {0x03, 0x07,  0x0B, 0x0E, 0x11, 0x14};

/** Registers definitions for the indexes. */
static const int position_registers[] = {0x00, 0x04, 0x08, 0x0C, 0x0F, 0x12};    

/** Index registers definition. */
static const int index_registers[] = {0x01, 0x05, 0x09};

/** Current sensing registers definition. */
static const int current_registers[] = {0x02, 0x06, 0x0A, 0x0D, 0x10, 0x13};  

#define DC_PWM_MAX_VALUE 475


void cvra_dc_set_pwm(void *device, int channel, int32_t value) {
    if(channel < 0 || channel > 5)
        return;

    if(value < -DC_PWM_MAX_VALUE)
        value = -DC_PWM_MAX_VALUE;

    if(value > DC_PWM_MAX_VALUE)
        value = DC_PWM_MAX_VALUE;

    /* XXX value clamping. */
    IOWR(device, pwm_registers[channel], value);
}


int32_t cvra_dc_get_encoder(void *device, int channel) {
    if(channel < 0 || channel > 5)
        return -1;

    return IORD(device, position_registers[channel]);
}

void cvra_dc_set_encoder(void *device, int channel, int32_t value) {
    if(channel < 0 || channel > 5)
        return;

    IOWR(device, position_registers[channel], value);
}

int32_t cvra_dc_get_index(void *device, int channel) {
    if(channel < 0 || channel > 2)
        return 0;

    return IORD(device, index_registers[channel]);
}

void cvra_dc_set_index(void *device, int channel, int32_t value) {
    if(channel < 0 || channel > 2)
        return;

    IOWR(device, index_registers[channel], value);
}

int32_t cvra_dc_get_current(void *device, int channel) {
    if(channel < 0 || channel > 5)
        return 0;

    return IORD(device, current_registers[channel]);
}

void cvra_dc_set_pwm0(void *device, int32_t value) {
    cvra_dc_set_pwm(device, 0, value);
}

void cvra_dc_set_pwm1(void *device, int32_t value) {
    cvra_dc_set_pwm(device, 1, value);
}

void cvra_dc_set_pwm2(void *device, int32_t value) {
    cvra_dc_set_pwm(device, 2, value);
}

void cvra_dc_set_pwm3(void *device, int32_t value) {
    cvra_dc_set_pwm(device, 3, value);
}

void cvra_dc_set_pwm4(void *device, int32_t value) {
    cvra_dc_set_pwm(device, 4, value);
}

void cvra_dc_set_pwm5(void *device, int32_t value) {
    cvra_dc_set_pwm(device, 5, value);
}

int32_t cvra_dc_get_encoder0(void *device) {
    return cvra_dc_get_encoder(device, 0);
}

int32_t cvra_dc_get_encoder1(void *device) {
    return cvra_dc_get_encoder(device, 1);
}

int32_t cvra_dc_get_encoder2(void *device) {
    return cvra_dc_get_encoder(device, 2);
}

int32_t cvra_dc_get_encoder3(void *device) {
    return cvra_dc_get_encoder(device, 3);
}

int32_t cvra_dc_get_encoder4(void *device) {
    return cvra_dc_get_encoder(device, 4);
}

int32_t cvra_dc_get_encoder5(void *device) {
    return cvra_dc_get_encoder(device, 5);
}

int32_t cvra_dc_get_index0(void *device){
    return cvra_dc_get_index(device, 0);
}

int32_t cvra_dc_get_index1(void *device){
    return cvra_dc_get_index(device, 1);
}

int32_t cvra_dc_get_index2(void *device){
    return cvra_dc_get_index(device, 2);
}
