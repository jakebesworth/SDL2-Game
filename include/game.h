/*  
 * game.h
 *
 * All game functions go here
 *
 */

#ifndef GAME_
#define GAME_

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
 *
 * @return the newly created object
 *
 */
Object * createObject(SDL_Texture * image, int subImage, int subImageNumber, objectType type, int x, int y, int w, int h);

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
 * Update an objects subimage to the next one in the chain
 *
 * @param obj   The object to update
 *
 */
void updateObjectAnimation(Object * obj);

/*  
 * General function to update all user-based actions
 *
 * @param ship      The ship object of the user
 * @param bullets   The bullets object chain
 * @param image     The user's spritesheet for creating bullets
 * @param timer     The global timer for checking bullet creation speed
 *
 * @return the bullet chain updated
 *
 */
Object * updateUserActions(Object * ship, Object * bullets, SDL_Texture * image, uint32_t * timer);

/*  
 * Update the user's ship based on keyboard input
 *
 * @param ship  The user ship object
 *
 */
void updateUserShipMovement(Object * ship);

/*  
 * Update all the bullet objects based on user actions
 *
 * @param ship      The user ship for where to spawn new bullets
 * @param bullets   The bullet chain of objects for which to check
 * @param image     The spritesheet that contains the bullet sprites
 * @param timer     The global timer for checking bullet creation speed
 *
 * @return the bullet chain updated
 *
 */
Object * updateUserBullets(Object * ship, Object * bullets, SDL_Texture * image, uint32_t * timer);

/*  
 * Update the asteroids object chain
 *
 * @param asteroids     The asteroids object chain
 * @param image         The spritesheet that contains the asteroids
 *
 * @return the asteroids object chain once it's been updated
 *
 */
Object * updateAsteroids(Object * asteroids, SDL_Texture * image);

/*  
 * Free object chain
 *
 * @param obj   The object chain to be freed
 *
 */
void freeObjects(Object * obj);

/*  
 * Game setup function, setup game settings and constants and initialize SDL2
 *
 */
void setup();

/*  
 * Count the object chain
 *
 * @param obj   The object chain to count
 *
 * @return number of objects in the chain
 *
 */
int countObjects(Object * obj);
#endif
