/*  
 * display.h
 *
 * The heads up display functions
 *
 */

#ifndef DISPLAY_
#define DISPLAY_

#ifdef __cplusplus
extern "C"
{
#endif


/*  
 * Display text in middle of the screen
 *
 * @param font  Font to use
 * @param text  Text to display
 * @param type  Type of Font
 *
 */
void displayTextMiddle(SDL_Texture * font, char * text, objectType type);

/*  
 * Display the game over message
 *
 * @param font      The font-sheet to use
 *
 */
void displayGameOver(SDL_Texture * font);


/*  
 * Display the user's heads up display
 *
 * @param ship  The ship to get lives
 * @param font  The font to use when printing HUD elements
 * @param timer The game seconds timer of the user in the world
 *
 */
void displayHUD(Object * ship, SDL_Texture * font, uint32_t timer);

#ifdef __cplusplus
}
#endif

#endif
