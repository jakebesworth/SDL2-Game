/*  
 * display.h
 *
 * The heads up display functions
 *
 */

#ifndef DISPLAY_
#define DISPLAY_

/*  
 * Display the heads up display
 *
 * @param ship      The ship Object (lives)
 * @param font      The font to use
 *
 */
void displayHUD(Object * ship, SDL_Texture * font);
#endif
