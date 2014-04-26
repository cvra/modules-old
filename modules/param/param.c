#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "param.h"

#ifdef COMPILE_ON_ROBOT
#include <ucos_ii.h>
static OS_CPU_SR cpu_sr;
#define LOCK() {OS_ENTER_CRITICAL();}
#define UNLOCK() {OS_EXIT_CRITICAL();}
#else
#define LOCK() {}
#define UNLOCK() {}
#endif

static param_t *param_list_head = NULL;

void param_add(param_t *p, const char *name, const char *desc)
{
    p->name = name;
    p->desc = desc;
    p->val = 0;
    LOCK();
    p->next = param_list_head;
    param_list_head = p;
    p->changed = false;
    UNLOCK();
}

bool param_has_changed(param_t *p)
{
    return p->changed;
}

double param_get(param_t *p)
{
    LOCK();
    p->changed = false;
    double v = p->val;
    UNLOCK();
    return v;
}

void param_set(param_t *p, double val)
{
    LOCK();
    p->val = val;
    p->changed = true;
    UNLOCK();
}

int param_list(char *buf, int bufsz)
{
    int remaining_sz = bufsz;
    LOCK();
    param_t *p = param_list_head;
    UNLOCK();
    while (p != NULL) {
        int ret;
        if (p->desc == NULL)
            ret = snprintf(buf, remaining_sz, "%s : %f\n", p->name, p->val);
        else
            ret = snprintf(buf, remaining_sz, "%s (%s): %f\n", p->name, p->desc, p->val);
        if (ret < 0) // encoding error
            return -1;
        if (ret < remaining_sz) {
            buf += ret;
            remaining_sz -= ret;
        } else { // buffer too small
            return -2;
        }
        p = p->next;
    }
    return 0;
}


static param_t *param_find(const char *param_name)
{
    LOCK();
    param_t *p = param_list_head;
    UNLOCK();
    while (p != NULL) {
        if (strcmp(p->name, param_name) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}

bool param_read_by_name(const char *param_name, double *val)
{
    param_t *p = param_find(param_name);
    if (p) {
        LOCK();
        *val = p->val;
        UNLOCK();
        return true;
    } else {
        return false;
    }
}

bool param_get_by_name(const char *param_name, double *val)
{
    param_t *p = param_find(param_name);
    if (p) {
        *val = param_get(p);
        return true;
    } else {
        return false;
    }
}

bool param_set_by_name(const char *param_name, double val)
{
    param_t *p = param_find(param_name);
    if (p) {
        param_set(p, val);
        return true;
    } else {
        return false;
    }
}

