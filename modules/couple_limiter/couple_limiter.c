/*
 * couple_limiter.c
 *
 *  Created on: 8 févr. 2012
 *      Author: Antoine Albertelli
 */

#include <stdlib.h>

#include "couple_limiter.h"

void couple_limiter_init(struct couple_limiter *c) {
	c->couple_limit = 0;
	c->old_feedback = 0;
	c->related_cs = NULL;
}

int32_t couple_limiter_do_filter(void *v, int32_t in) {
	int32_t real_speed;
	struct couple_limiter *c = (struct couple_limiter *)v;
	if(c->related_cs == NULL) return in;
	if(c->couple_limit == 0) return in;

	real_speed = cs_get_filtered_feedback(c->related_cs) - c->old_feedback;

	if(abs(in - real_speed) > c->couple_limit) {
		in = (int)((float)in * ((float)c->couple_limit / (float)abs(in - real_speed)));
	}

	c->old_feedback = cs_get_filtered_feedback(c->related_cs);

	return in;
}

void couple_limiter_set_limit(struct couple_limiter *c, int32_t limit) {
	c->couple_limit = limit;
}

void couple_limiter_set_related_cs(struct couple_limiter *c, struct cs *r) {
	c->related_cs = r;
}

