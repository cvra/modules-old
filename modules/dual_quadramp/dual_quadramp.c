/*
 * dual_quadramp.c
 *
 *  Created on: 19 avr. 2012
 *      Author: Antoine Albertelli (CVRA)
 */

#include <dual_quadramp.h>

#define abs(x) ((x)<0 ? -(x) : (x))

void dual_quadramp_init(struct dual_quadramp_filter *q) {
	int32_t flags;
	IRQ_LOCK(flags);
	quadramp_init(&q->x_quadramp);
	quadramp_init(&q->y_quadramp);
	q->x_pos = q->x_consign = 0;
	q->y_pos = q->y_consign = 0;
	IRQ_UNLOCK(flags);
}


void dual_quadramp_do_filter(struct dual_quadramp_filter *q) {
	int32_t x_speed, y_speed;
	int32_t x_acc, y_acc;

	int x_distance, y_distance;

	x_distance = abs(q->x_pos - q->x_consign);
	y_distance = abs(q->y_pos - q->y_consign);

	x_speed = (int32_t)(q->speed * x_distance / (float)(x_distance + y_distance));
	y_speed = (int32_t)(q->speed * y_distance / (float)(x_distance + y_distance));

	x_acc = (int32_t)(q->acc * x_distance / (float)(x_distance + y_distance));
	y_acc = (int32_t)(q->acc * y_distance / (float)(x_distance + y_distance));


	quadramp_set_1st_order_vars(&q->x_quadramp, x_speed, x_speed);
	quadramp_set_2nd_order_vars(&q->x_quadramp, x_acc, x_acc);

	quadramp_set_1st_order_vars(&q->y_quadramp, y_speed, y_speed);
	quadramp_set_2nd_order_vars(&q->y_quadramp, y_acc, y_acc);

	q->x_pos = quadramp_do_filter((void *)&q->x_quadramp, q->x_consign);
	q->y_pos = quadramp_do_filter((void *)&q->y_quadramp, q->y_consign);
}

void dual_quadramp_get_pos(struct dual_quadramp_filter *q, int32_t *x, int32_t *y) {
	*x = q->x_pos;
	*y = q->y_pos;
}

void dual_quadramp_set_pos(struct dual_quadramp_filter *q, int32_t x, int32_t y) {
	quadramp_set_position(&q->x_quadramp, x);
	quadramp_set_position(&q->y_quadramp, y);

	q->x_pos = x;
	q->y_pos = y;
}

void dual_quadramp_set_acc_and_speed(struct dual_quadramp_filter *q, int32_t speed, int32_t acc) {
	q->acc = acc;
	q->speed = speed;
}


