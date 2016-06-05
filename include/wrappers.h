/*  
 * wrappers.h
 *
 * All SDL wrapper functions declarations go here
 *
 */

#ifndef WRAPPERS_
#define WRAPPERS_

#ifdef __cplusplus
extern "C"
{
#endif

/*  
 * Apply Texture with extra options to global renderer
 *
 * @param x         The x coordinate to apply on the renderer
 * @param y         The y coordinate to apply on the renderer
 * @param source    The source Texture to apply
 * @param clip      The Texture clip of the object on the spritesheet
 * @param scale     The scale of how object is displayed (1.0 for no scaling)
 * @param angle     The angle on which to rotate
 * @param center    The point on which to rotate (NULL for middle)
 * @param flip      SDL_FLIP_* where * is NONE, HORIZONTAL, VERTICAL
 *
 */
void applyTextureEx(int x, int y, SDL_Texture * source, SDL_Rect * clip, float scale, double angle, SDL_Point * center, SDL_RendererFlip flip);

/*  
 * Modify texture color by: color = color * (newcolor / 255)
 *
 * @param texture       Texture to modify
 * @param r             R color value
 * @param g             G color value
 * @param b             B color value
 *
 */
void setTextureColorMod(SDL_Texture * texture, uint8_t r, uint8_t g, uint8_t b);

/*  
 * Sets the window icon in the tray
 * Note: background transparency color is RGB(0,0,0)
 *
 * @param image     The image path to load
 *
 */
void setWindowIcon(char * image);

/*  
 * Set the global renderer color
 *
 * @param r     R color
 * @param g     G color
 * @param b     B color
 * @param a     Alpha value
 *
 */
void setWindowColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

/*  
 * Set window height and width
 * Note: The window size in screen coordinates may different from in pixels
 *
 * @param width     The width in pixels to set
 * @param height    The height in pixels to set
 *
 */
void setWindowSize(int width, int height);

/*  
 * Get native resolution height
 *
 * @return native resolution height
 *
 */
int getNativeHeight();

/*  
 * Get native resolution width
 *
 * @return native resolution width
 *
 */
int getNativeWidth();

/*  
 * Get the absolute path to a relative to directory root path
 *
 * @param relativeString    The relative path
 *
 * @return a pointer to function's static memory containing the absolute path of the given relative path
 *
 */
char * getAbsolutePath(char * relativeString);

/*  
 * Set the alpha layer onto a texture
 *
 * @param texture   The texture to set alpha to
 * @param alpha     The alpha number 0-255
 *
 */
void setTextureAlpha(SDL_Texture * texture, uint8_t alpha);

/*  
 * Load new SDL Texture
 *
 * @param image     Path to the image to load
 * @param surface   Optional parameter, preloaded SDL Surface or NULL to create
 *
 * @return the newly loaded SDL Texture
 *
 */
SDL_Texture * loadTexture(char * image, SDL_Surface * surface);

/*  
 * Load new SDL Texture with background colour removed
 *
 * @param image     Path to the image to load
 * @param colourR   (R)GB colour to be removed
 * @param colourG   R(G)B colour to be removed
 * @param colourB   RG(B) colour to be removed
 *
 * @return the newly loaded SDL Texture
 *
 */
SDL_Texture * loadTextureBack(char * image, uint8_t colourR, uint8_t colourG, uint8_t colourB);

/*  
 * Apply Texture to global renderer
 *
 * @param x         The x coordinate to apply on the renderer
 * @param y         The y coordinate to apply on the renderer
 * @param source    The source Texture to apply
 * @param clip      The Texture clip of the object on the spritesheet
 * @param scale     The scale of how object is displayed (1.0 for no scaling)
 *
 */
void applyTexture(int x, int y, SDL_Texture * source, SDL_Rect * clip, float scale);

/*  
 * Initialize SDL
 *
 * @param title     The window title
 *
 * @return 1 on success 0 on failure 
 *
 */
int initSDL(char * title);

/*  
 * Clear the renderer to the last set colour
 *
 */
void clearScreen();

/*  
 * Delay the game by the remaining frames per second
 *
 * @param timer     The global timer
 *
 */
void delayFramesPerSecond(uint32_t timer);

/*  
 * Update the window with the latest renderer
 *
 */
void updateWindow();

#ifdef __cplusplus
}
#endif

#endif
