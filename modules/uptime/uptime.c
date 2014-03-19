#include <uptime.h>

#ifdef __unix__
static int32_t uptime_value = 0;

void uptime_set(int32_t time)
{
    uptime_value = time;
}

#endif

int32_t uptime_get(void)
{
#ifdef COMPILE_ON_ROBOT
    return (IORD(TIMECOUNTER_BASE, 0));
#else
    return uptime_value;
#endif
}


