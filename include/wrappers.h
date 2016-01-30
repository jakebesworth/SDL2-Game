/*  
 * wrappers.h
 *
 * 
 *
 */

#ifndef WRAPPERS_
#define WRAPPERS_

SDL_Texture * loadTexture(char * image, SDL_Surface * surface);
SDL_Texture * loadTextureBack(char * image, uint8_t colourR, uint8_t colourG, uint8_t colourB);
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
