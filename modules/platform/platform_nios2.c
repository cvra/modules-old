
#include <platform.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void reset(void)
{
    printf("%s()\n", __FUNCTION__);
    exit(EXIT_SUCCESS);
}

void panic(void)
{
    printf("%s()\n", __FUNCTION__);
    exit(EXIT_FAILURE);
}

void platform_create_semaphore(semaphore_t *sem, int count)
{
    sem->count = count;
    sem->acquired_count = 0;
}


void platform_signal_semaphore(semaphore_t *sem)
{
    sem->count++;
}

void platform_take_semaphore(semaphore_t *sem)
{
    if (sem->count > 0) {
        sem->count--;
        sem->acquired_count++;
    }
}


