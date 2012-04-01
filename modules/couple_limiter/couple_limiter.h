/** @file couple_limiter.h
 * 
 * @brief Ce module est charge de limiter le couple induit par les roues
 * pour eviter que nos pneus fragiles s'abiment.
 * 
 * @date 8.2.2012
 * @author Antoine Albertelli
 * @todo Il faudra peut etre ajouter des coef de bricolage sur le calcul du couple.
 * du couple.
 */

#ifndef COUPLE_LIMITER_H_
#define COUPLE_LIMITER_H_

#include <aversive.h>
#include <control_system_manager.h>

/** Structure contenant toutes les variables utiles a ce module. */
struct couple_limiter {
	int32_t couple_limit;
	int32_t old_feedback; // pour calculer la vitesses
	struct cs *related_cs;
};

/** Reset le module */
void couple_limiter_init(struct couple_limiter *c);

/** Fais une iteration du filtre. */
int32_t couple_limiter_do_filter(void *v, int32_t in);

/** Set la limite de couple. */
void couple_limiter_set_limit(struct couple_limiter *c, int32_t limit);

/** Set la boucle de controle a limiter. */
void couple_limiter_set_related_cs(struct couple_limiter *c, struct cs *r);

#endif /* COUPLE_LIMITER_H_ */
