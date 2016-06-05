/*  
 * types.h
 *
 * All custom game types and enumerations are defined here
 *
 */

#ifndef TYPES_
#define TYPES_

#ifdef __cplusplus
extern "C"
{
#endif

/*  
 * Types to distinguish objects
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
    FONT_MEDIUM,
    FONT_LARGE,
    OBJECT_TYPE_SIZE
} objectType;

/*  
 * Game enumerated states
 *
 */
typedef enum
{
    DEFAULT,
    CUTSCENE,
    MENU,
    WAVE,
    PAUSE,
    GAME_STATE_SIZE
} gameState;

/*  
 * Timer indexes
 *
 */
typedef enum
{
    GLOBAL_TIMER,
    BULLET_TINY_TIMER,
    DISPLAY_GAME_TIMER,
    TIMER_TYPE_SIZE
} timerType;

/*  
 * Definition for game objects
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
    int16_t lives;
    float scale;
    struct object * next;
} Object;

/*
 * Definition for the game global variables
 *
 */
typedef struct globalSDL
{
    /* Game constants */
    uint16_t screenWidth;
    uint16_t screenHeight;
    float screenTop;
    float screenBottom;
    float screenLeft;
    float screenRight;
    float framesPerSecond;
    float gameTickRatio;

    /* Base path of game directory */
    char * basePath;

    /* global SDL objects */
    SDL_Window * window;
    SDL_Renderer * renderer;
    const uint8_t * keystates;

    /* Game running flag */
    uint8_t exit;

    /* Game is state base */
    gameState state;

    /* Game timers */
    uint32_t timer[TIMER_TYPE_SIZE];
} GlobalSDL;

#ifdef __cplusplus
}
#endif

#endif
