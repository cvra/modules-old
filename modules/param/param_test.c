

#include <stdio.h>
#include "param.h"

int main(void)
{
    param_t x,y;
    param_add(&x, "x", "x desc");
    param_add(&y, "y", NULL);

    char buf[100];
    param_list(buf, sizeof(buf));
    printf("%s\n", buf);

    param_t z;
    printf("z changed %d\n", param_has_changed(&z));
    param_add(&z, "z", "z param");
    param_set(&z, 23);
    printf("z changed %d\n", param_has_changed(&z));
    printf("get z = %f\n", param_get(&z));
    printf("z changed %d\n", param_has_changed(&z));

    double zv;
    if (param_read_by_name("z", &zv))
        printf("%f\n", zv);
    else
        printf("not found\n");

    param_list(buf, sizeof(buf));
    printf("%s\n", buf);

    param_set_by_name("x", 42);

    param_list(buf, sizeof(buf));
    printf("%s\n", buf);
}
