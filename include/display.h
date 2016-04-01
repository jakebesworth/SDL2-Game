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
 * Display a string as a text object in the middle of the window
 *
 * @param font      The font-sheet to use
 * @param text      The string to convert to a text object
 *
 */
void displayTextMiddle(SDL_Texture * font, char * text);

/*  
 * Display the game over message
 *
 * @param font      The font-sheet to use
 *
 */
void displayGameOver(SDL_Texture * font);

/*  
 * Display the heads up display
 *
 * @param ship      The ship Object (lives)
 * @param font      The font to use
 *
 */
void displayHUD(Object * ship, SDL_Texture * font);

#ifdef __cplusplus
}
#endif

#endif
