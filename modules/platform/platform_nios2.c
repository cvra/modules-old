
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
    sem->sem = OSSemCreate((INT16U)count);
}


void platform_signal_semaphore(semaphore_t *sem)
{
    OSSemPost(sem->sem);
}

void platform_take_semaphore(semaphore_t *sem)
{
    INT8U err;
    OSSemPend(sem->sem, 0, &err);
}


