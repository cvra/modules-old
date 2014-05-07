#include <aversive.h>
#include <uptime.h>

#ifdef __unix__
static timestamp_t uptime_value = 0;

void uptime_set(timestamp_t time)
{
    uptime_value = time;
}

#endif

timestamp_t uptime_get(void) {
#ifdef COMPILE_ON_ROBOT
    return (IORD(TIMECOUNTER_BASE, 0));
#else
    return uptime_value;
#endif
}


