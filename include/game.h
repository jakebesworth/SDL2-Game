/*  
 * game.h
 *
 * Game logic and orginization functions go here
 *
 */

#ifndef GAME_
#define GAME_

#ifdef __cplusplus
extern "C"
{
#endif

void endSDL();

/*  
 * Update all object collisions
 *
 * @param ship      Ship object to check collisions
 * @param bullets   Bullets object to check collisions
 * @param asteroids Asteroids object to check collisions
 *
 */
void updateObjectCollision(Object ** ship, Object ** bullets, Object ** asteroids);

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
 * Game setup function, setup game settings and constants and initialize SDL2
 *
 */
void startSDL();

#ifdef __cplusplus
}
#endif

#endif
