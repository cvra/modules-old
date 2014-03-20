#ifndef _PLATFORM_HOST_H
#define _PLATFORM_HOST_H

#include <stdint.h>

/** Reimplementation de IORD du NIOS2 pour compiler sur le PC */
#define IORD(adress, offset) (*((int32_t *)adress+offset))

/** Reimplementation de IOWR du NIOS2 pour compiler sur le PC */
#define IOWR(adress, offset, data) (*((int32_t *)adress+offset) = data)

typedef struct {
    int count;
    int acquired_count;
} semaphore_t;

void platform_create_semaphore(semaphore_t *sem, int count);
void platform_signal_semaphore(semaphore_t *sem);
void platform_take_semaphore(semaphore_t *sem);

#endif
