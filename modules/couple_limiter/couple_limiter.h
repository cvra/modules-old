/*
 * couple_limiter.h
 *
 *  Created on: 8 févr. 2012
 *      Author: Antoine Albertelli
 */

#ifndef COUPLE_LIMITER_H_
#define COUPLE_LIMITER_H_

#include <aversive.h>
#include <control_system_manager.h>

struct couple_limiter {
	int32_t couple_limit;
	int32_t old_feedback; // pour calculer la vitesses
	struct cs *related_cs;
};

void couple_limiter_init(struct couple_limiter *c);
int32_t couple_limiter_do_filter(void *v, int32_t in);

void couple_limiter_set_limit(struct couple_limiter *c, int32_t limit);
void couple_limiter_set_related_cs(struct couple_limiter *c, struct cs *r);

#endif /* COUPLE_LIMITER_H_ */
