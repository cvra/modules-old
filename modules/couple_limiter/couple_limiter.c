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
	c->maximum_reached = 0;
}

int32_t couple_limiter_do_filter(void *v, int32_t in) {
	int32_t real_speed;
	struct couple_limiter *c = (struct couple_limiter *)v;
	if(c->related_cs == NULL) return in;


	real_speed = cs_get_filtered_feedback(c->related_cs) - c->old_feedback;

	c->couple = abs(in - real_speed);

	if(c->couple_limit == 0) return in;

	if(abs(in - real_speed) > c->couple_limit) {
		in = (int)((float)in * ((float)c->couple_limit / (float)abs(in - real_speed)));
		c->maximum_reached = 1;
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

int couple_limiter_get_couple(struct couple_limiter *c) {
	return c->couple;
}

int couple_limiter_max_couple_reached(struct couple_limiter *c) {
	return c->maximum_reached;
}


