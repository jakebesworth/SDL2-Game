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
 * @param surface
 *
 * @return 
 *
 */
SDL_Texture * loadTexture(char * image, SDL_Surface * surface);

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
SDL_Texture * loadTextureBack(char * image, uint8_t colourR, uint8_t colourG, uint8_t colourB);

/*  
 * 
 *
 * @param x
 * @param y
 * @param source
 * @param clip
 *
 */
void applyTexture(int x, int y, SDL_Texture * source, SDL_Rect * clip);

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
