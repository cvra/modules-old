/*
 * torque_limiter.c
 *
 *  Created on: 8 févr. 2012
 *      Author: Antoine Albertelli
 */

#include <stdlib.h>

#include "torque_limiter.h"

void torque_limiter_init(struct torque_limiter *c) {
	c->torque_limit = 0;
	c->old_feedback = 0;
	c->related_cs = NULL;
	c->maximum_reached = 0;
}

int32_t torque_limiter_do_filter(void *v, int32_t in) {
	int32_t real_speed;
	struct torque_limiter *c = (struct torque_limiter *)v;
	if(c->related_cs == NULL) return in;


	real_speed = cs_get_filtered_feedback(c->related_cs) - c->old_feedback;

	c->torque = abs(in - real_speed);

	if(c->torque_limit == 0) return in;

	if(abs(in - real_speed) > c->torque_limit) {
		in = (int)((float)in * ((float)c->torque_limit / (float)abs(in - real_speed)));
		c->maximum_reached = 1;
	}



	c->old_feedback = cs_get_filtered_feedback(c->related_cs);

	return in;
}

void torque_limiter_set_limit(struct torque_limiter *c, int32_t limit) {
	c->torque_limit = limit;
}

void torque_limiter_set_related_cs(struct torque_limiter *c, struct cs *r) {
	c->related_cs = r;
}

int torque_limiter_get_torque(struct torque_limiter *c) {
	return c->torque;
}

int torque_limiter_max_torque_reached(struct torque_limiter *c) {
	return c->maximum_reached;
}

void torque_limiter_reset(struct torque_limiter *c) {
	c->maximum_reached = 0;
}


