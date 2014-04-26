#ifndef PARAM_H
#define PARAM_H

#include <stdint.h>
#include <stdbool.h>

typedef struct param_s param_t;

struct param_s {
    double val;
    bool changed;
    const char *name;
    const char *desc;
    // internals
    param_t *next;
};

// desc can be NULL
void param_add(param_t *p, const char *name, const char *desc);

// returns whether the parameter has changed since last get()
bool param_has_changed(param_t *p);

// sets changed to false
double param_get(param_t *p);

// sets changed to true
void param_set(param_t *p, double val);

// returns 0 on success, -1 on error, -2 if the buffer is too small
int param_list(char *buf, int bufsz);

// does NOT set changed to false
bool param_read_by_name(const char *param_name, double *val);

// sets changed to false
bool param_get_by_name(const char *param_name, double *val);

// sets changed to true
bool param_set_by_name(const char *param_name, double val);

#endif // PARAM_H
