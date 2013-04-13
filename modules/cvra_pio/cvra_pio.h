#ifndef _CVRA_PIO_H_
#define _CVRA_PIO_H_


/** Writes a value to a digital output.
 * @param [in] channel The IO channel to change.
 * @param [in] value The value to set the pin to.
 */
void cvra_pio_set(int channel, int value);

/** Gets the value of a digital input.
 * @param [in] channel The IO channel to read.
 * @returns The read value or -1 in case of error.
 */
int cvra_pio_get(int channel);


#endif
