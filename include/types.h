/*  
 * types.h
 *
 * 
 *
 */

#ifndef TYPES_
#define TYPES_

/*  
 * 
 *
 */
typedef enum
{
    SHIP,
    BULLET_TINY,
    ASTEROID_SMALL,
    ASTEROID_MEDIUM,
    ASTEROID_LARGE,
    OBJECT_TYPE_SIZE
} objectType;


/*  
 * 
 *
 */
typedef enum
{
    BULLET_TINY_TIMER,
    TIMER_TYPE_SIZE
} timerType;

/*  
 * Object type
 *
 */
typedef struct object
{
    objectType type;
    SDL_Surface * image;
    SDL_Rect clip;
    uint16_t subImage;
    uint16_t subImageNumber;
    int x;
    int y;
    struct object * next;
} Object;
#endif
