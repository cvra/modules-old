/**
 * here are some cute little macros, and other stuff, microcontroller
 * related ! 
 */


#ifndef _AVERSIVE_H_
#define _AVERSIVE_H_

#include <inttypes.h>

 /** @brief Computes the absolute value of a number 
 *
 *  While the abs() function in the libc works only with int type
 *  this macro works with every numerical type including floats
 *
 *  @note On float this is a bad idea, fabs() is faster. 
 */
#define ABS(val) ({					\
			__typeof(val) __val = (val);	\
			if (__val < 0)			\
				__val = - __val;	\
			__val;				\
		})

/* a few asm utilities */

#ifndef COMPILE_ON_ROBOT
/* On X86 */

#include <stdio.h>
#define reset() 

#define panic() do {printf("PANIC MOTHERFUCKER!!!\n"); }while(1)

#else
/* Si on est ici c'est qu'on compile pour le NIOS II. */
/** Resets the robot by jumping to the reset address.
 * @bug L'adresse de retour est hardcodee (0x04000000). pas bien...
 * @note Found on http://www.altera.com/support/kdb/solutions/rd05062005_584.html */
#define reset() do {                         \
    NIOS2_WRITE_STATUS(0);                   \
    NIOS2_WRITE_IENABLE(0);                  \
    ((void (*) (void)) 0x00000000) (); 		 \
    } while(0)

/** This define is called whenever the code hits a fatal crash. */
#define panic() do { \
    EMERG(0, "kernel panic"); \
} while(1)
   
#endif


#endif /* ifndef _AVERSIVE_H_ */

