#ifndef _UPTIME_H_

#include <platform.h>


/** Returns uptime of the robot
 *
 * Returns time passed since booting the system with a resolution of 1us. This time is counted
 * by a hardware-timer, so there is no precision drop when the CPU is heavily loaded.
 *
 * @note: the value is stored on 32 bit so the counter overflows after ~1h 11min
 * Therefore this module is not intended to be an RTC but works well as a general purpose timer
 *
 * @note: the function triggers a bus transaction (bypassing the cache) which may impact performance
 *
 *@todo: returns zero when run in simulation
 */

int32_t uptime_get(void);

#ifdef __unix__

/* Test mock. */
void uptime_set(int32_t time);
#endif

#endif
