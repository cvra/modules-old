#include <platform.h>
#include <stdio.h>
#include <stdlib.h>


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


