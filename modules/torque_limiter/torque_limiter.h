/** @file torque_limiter.h
 * 
 * @brief This module is responsible for limiting applied torque on a motor to
 * prevent damage to our wheels.
 * 
 * @date 8.2.2012
 * @author Antoine Albertelli
 * @todo Il faudra peut etre ajouter des coef de bricolage sur le calcul du torque.
 */

#ifndef TORQUE_LIMITER_H_
#define TORQUE_LIMITER_H_

#include <aversive.h>
#include <control_system_manager.h>

/** Structure for holding all the internal variables of the module. */
struct torque_limiter {
	int32_t torque_limit;
	int32_t old_feedback; // pour calculer la vitesses
	struct cs *related_cs;
	int torque;			// pour la calibration
	int maximum_reached; /// =1 si le torque maximum a ete atteint
};

/** Reset the module */
void torque_limiter_init(struct torque_limiter *c);

/** Computes a single filter iteration.
 *
 * @returns Filter output.  */
int32_t torque_limiter_do_filter(void *v, int32_t in);

/** Sets torque limit. */
void torque_limiter_set_limit(struct torque_limiter *c, int32_t limit);

/** Sets control system whose torque is to be regulated. */
void torque_limiter_set_related_cs(struct torque_limiter *c, struct cs *r);

/** Returns the last computed torque of the filter. */
int torque_limiter_get_torque(struct torque_limiter *c);

/** Returns 1 if the maximal torque was reached after the last call to
 * torque_limiter_reset was issued. */
int torque_limiter_max_torque_reached(struct torque_limiter *c);

/** Resets the state of the filter. */
void torque_limiter_reset(struct torque_limiter *c);

#endif /* TORQUE_LIMITER_H_ */
