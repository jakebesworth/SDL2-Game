/*  
 * object.h
 *
 * All object type related functions
 *
 */

#ifndef OBJECT_
#define OBJECT_

#ifdef __cplusplus
extern "C"
{
#endif

/*  
 * Get the Length of a text object
 *
 * @param obj       Text object to get length of
 * @param extra     Any extra letters you want to add to the equation
 *
 * @return the float value of the object length
 *
 */
float getTextObjectLength(Object * obj, int extra);

/*  
 * Check object collisions
 *
 * @param obj1  The first object
 * @param obj2  The second object
 *
 * @return 1 on collision, 0 on no collision
 *
 */
int objectCollision(Object * obj1, Object * obj2);

/*  
 * Set an object chain alpha
 *
 * @param obj       The object chain to set alpha
 * @param alpha     The alpha level 0-255
 *
 */
void setObjectAlpha(Object * obj, uint8_t alpha);

/*  
 * Create a text object from a string
 *
 * @param image     The SDL Texture to use
 * @param text      The string to build from
 * @param type      The type of font (tiny, small, large...)
 * @param scale     The scale of how object is displayed (1.0 for no scaling)
 *
 * @return a text object, a chain of character objects
 *
 */
Object * createTextObject(SDL_Texture * image, char * text, objectType type, float scale);

/*  
 * Get the text X position in a font-sheet
 *
 * @param c     The character to check against
 *
 * @return      The x index of where the character is on the font-sheet
 *
 */
int getTextX(char c);

/*  
 * Get the text Y position in a font-sheet
 *
 * @param c     The character to check against
 *
 * @return      The y index of where the character is on the font-sheet
 *
 */
int getTextY(char c);

/*  
 * Move a text object chain relative to x and y
 *
 * @param obj       The text object chain to move
 * @param x         The relative x position to move to
 * @param y         The relative y position to move to
 *
 */
void moveTextObject(Object * obj, int x, int y);

/*  
 * Position a text object chain absolutely to x and y
 *
 * @param obj       The text object chain to move
 * @param x         The relative x position to move to
 * @param y         The relative y position to move to
 *
 */
void positionTextObject(Object * obj, int x, int y);

/*  
 * Create a new object
 *
 * @param image             The object texture to use (already instantiated)
 * @param subImage          The default animation subimage
 * @param subImageNumber    The number of total subimages in the spritesheet
 * @param type              The object type
 * @param x                 The x position on the spritesheet where the image starts
 * @param y                 The y position on the spritesheet where the image starts
 * @param w                 The image width (used for animation subimages)
 * @param h                 The image height (used for animation subimages)
 * @param scale             The scale of how object is displayed (1.0 for no scaling)
 *
 * @return the newly created object
 *
 */
Object * createObject(SDL_Texture * image, int subImage, int subImageNumber, objectType type, uint16_t lives, int x, int y, int w, int h, float scale);

/*  
 * Move an object relative x and y coordinates and set new object coordinates
 *
 * @param obj   The object to move
 * @param x     The x coordinate to move relatively
 * @param y     The y coordinate to move relatively
 *
 */
void moveObject(Object * obj, int x, int y);

/*  
 * Position the object at absolute x and y
 *
 * @param obj   The object to position
 * @param x     The absolute x coordinate
 * @param y     The absolute y coordinate
 *
 */
void positionObject(Object * obj, int x, int y);

/*  
 * Free object chain
 *
 * @param obj   The object chain to be freed
 *
 */
void freeObjects(Object * obj);

/*  
 * Count the object chain
 *
 * @param obj   The object chain to count
 *
 * @return number of objects in the chain
 *
 */
int countObjects(Object * obj);

#ifdef __cplusplus
}
#endif

#endif
