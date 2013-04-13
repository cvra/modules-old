#ifndef _CVRA_SERVO_H
#define _CVRA_SERVO_H

#include <aversive.h>

/** Sets the servo pulse width.
 * @todo Can we set pulse time > 20ms ? What happens then ? */
void cvra_servo_set(void *base, int channel, uint32_t value);

#endif
