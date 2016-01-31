/*  
 * types.h
 *
 * All custom game types and enumerations are defined here
 *
 */

#ifndef TYPES_
#define TYPES_

/*  
 * Object types to distinguish objects
 *
 */
typedef enum
{
    SHIP,
    BULLET_TINY,
    ASTEROID_SMALL,
    ASTEROID_MEDIUM,
    ASTEROID_LARGE,
    FONT_TINY,
    FONT_SMALL,
    OBJECT_TYPE_SIZE
} objectType;

/*  
 * Game state enumeration states
 *
 */
typedef enum
{
    DEFAULT,
    CUTSCENE,
    WAVE,
    PAUSE,
    GAME_STATE_SIZE
} gameState;

/*  
 * Timer indexes for global timer
 *
 */
typedef enum
{
    BULLET_TINY_TIMER,
    TIMER_TYPE_SIZE
} timerType;

/*  
 * Object definition for game objects
 *
 */
typedef struct object
{
    objectType type;
    SDL_Texture * image;
    SDL_Rect clip;
    uint16_t subImage;
    uint16_t subImageNumber;
    int x;
    int y;
    struct object * next;
} Object;
#endif
