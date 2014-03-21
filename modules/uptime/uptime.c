#include <uptime.h>

timestamp_t uptime_get(void) {
#ifdef COMPILE_ON_ROBOT
    return (IORD(TIMECOUNTER_BASE, 0));
#else
    return 0;
#endif
}
