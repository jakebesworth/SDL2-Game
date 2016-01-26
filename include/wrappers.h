/*  
 * wrappers.h
 *
 * 
 *
 */

#ifndef WRAPPERS_
#define WRAPPERS_

/*  
 * 
 *
 * @param image
 *
 * @return 
 *
 */
SDL_Surface * loadSurface(char * image);

/*  
 * 
 *
 * @param image
 * @param colourR
 * @param colourG
 * @param colourB
 *
 * @return 
 *
 */
SDL_Surface * loadSurfaceBack(char * image, uint8_t colourR, uint8_t colourG, uint8_t colourB);

/*  
 * 
 *
 * @param x
 * @param y
 * @param source
 * @param clip
 *
 */
void applySurface(int x, int y, SDL_Surface * source, SDL_Rect * clip);

/*  
 * 
 *
 * @param title
 *
 * @return 
 *
 */
int init(char * title);

/*  
 * 
 *
 */
void clearScreen();

/*  
 * 
 *
 * @param timer
 *
 */
void delayFramesPerSecond(uint32_t timer);

/*  
 * 
 *
 */
void updateWindow();
#endif
