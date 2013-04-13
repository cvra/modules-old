#include <aversive.h>
#include <cvra_pio.h>


/** Base adress of the PIO module.
 * @todo Change this value to reflect the real module. */
#ifdef PIO_BASE
 #undef PIO_BASE
#endif
#define PIO_BASE 0x00

/** The current value of the outputs. */
static int32_t output_value;

void cvra_pio_set(int channel, int value) {
    /* first 4 pins are for servo output. */
    if(channel < 4 || channel > 15)
        return;

    if(value) 
        output_value |= (1<<channel);
    else
        output_value &= ~(1<<channel); 

    IOWR(PIO_BASE, 0, channel);
}

int cvra_pio_get(int channel) {
    int16_t value = IORD(PIO_BASE, 0);
    return (value & (1 << channel)) != 0;
}
