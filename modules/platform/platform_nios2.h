#ifndef _PLATFORM_NIOS2_H_
#define _PLATFORM_NIOS2_H_

#include <stdint.h>
#include "os_cpu.h"
#include "os_cfg.h"
#include "ucos_ii.h"
#include <system.h>
#include <io.h>
#include <sys/alt_irq.h>

typedef struct {
    OS_EVENT*   sem;
} semaphore_t;

#endif
