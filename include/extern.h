/*  
 * extern.h
 *
 * All global variables / constants
 *
 */

#ifndef EXTERN_
#define EXTERN_

#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern GlobalSDL * Global;

/* Declare Numeric Game Constants */
extern float SHIP_SPEED;
extern float ASTEROID_SPEED;
extern float BULLET_TINY_SPEED;

/* Declare Global SDL Variables */
extern uint32_t score;

#ifdef __cplusplus
}
#endif

#endif
