#ifndef _UPTIME_H_

#include <aversive.h>

/** Returns robot uptime.
 *
 * Returns the uptime of the system with a 1us resolution. This time is computed
 * by an external hardware counter which is not influenced by a heavy CPU load.
 *
 * @note This is a 32 bit timer, which means it can only count up to 1 hour and
 * 11 minutes before overflow.
 *
 * @note Calling this function causes a bus transaction and a cache bypass which
 * means calling it too often can hurt performances.
 *
 * @todo This function always return 0 on simulator.
 */
int32_t uptime_get(void);

#endif
