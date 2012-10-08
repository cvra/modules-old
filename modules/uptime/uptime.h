#ifndef _UPTIME_H_


#include <aversive.h>

/** Retourne l'uptime. 
 *
 * Retourne le temps depuis le boot du systeme avec une resolution de 1us. Ce temps est compte par un timer
 * hardware, ce qui garantit la precision meme sous une forte charge CPU.
 *
 * @note La valeur est stockee sur 32 bits, soit 1h et 11 minutes avant overflow.
 * Ce module n'est donc pas adapte pour faire une RTC mais fonctionne bien comme
 * general purpose timer.
 *
 * @note Cette fonction declenche une transaction sur le bus (bypass du cache) ce qui
 * peut avoir des impacts sur les performances.
 *
 * @todo Cette fonction retourne toujours zero sur simulateur.
 */ 
int32_t uptime_get(void);

#endif
