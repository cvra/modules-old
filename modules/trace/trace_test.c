#include <stdio.h>

#include "trace.h"
#include "trace_over_ip.h"

int main(void)
{
    trace_var_t x, y, z;
    trace_var_add(&x, "x");
    trace_var_add(&y, "y");
    trace_var_add(&z, "z");
    trace_over_ip_init(10000);
    int vx = 0;
    while (1) {
        vx ++;
        trace_var_update(&x, vx);
        getchar();
    }
}

