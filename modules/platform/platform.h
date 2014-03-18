#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#ifdef COMPILE_ON_ROBOT
#include <platform_nios2.h>
#else
#include <platform_host.h>
#endif

/** @brief Resets the boards. */
void reset(void);

/** @brief Called after a non recoverable error. */
void panic(void);


#endif
