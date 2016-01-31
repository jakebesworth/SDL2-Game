/*  
 * global.h
 *
 * All generic functions and global variables declared here
 *
 */

#ifndef GLOBAL_
#define GLOBAL_

/* File Paths */
#define IMG_DIR "assets/img/"
#define FONT_DIR "assets/fonts/"
#define ERROR_FILE "logs/error_log"

/* Declare Numeric Game Constants */
extern uint16_t SCREEN_WIDTH;
extern uint16_t SCREEN_HEIGHT;
extern float SCREEN_TOP;
extern float SCREEN_BOTTOM;
extern float SCREEN_LEFT;
extern float SCREEN_RIGHT;
extern float FRAMES_PER_SECOND;
extern float GAME_TICK_RATIO;

extern float SHIP_SPEED;
extern float ASTEROID_SPEED;
extern float BULLET_TINY_SPEED;

/* Declare Global SDL Variables */
extern SDL_Window * window;
extern SDL_Renderer * renderer;
extern const uint8_t * keystates; 

/* General Functions */

/*  
 * Get the system date
 *
 * @return string of the current date
 *
 */
char * getDate();
#endif
