/*  
 * game.h
 *
 * 
 *
 */

#ifndef GAME_
#define GAME_

/*  
 * 
 *
 * @param image
 * @param subImage
 * @param subImageNumber
 * @param type
 * @param x
 * @param y
 * @param w
 * @param h
 *
 * @return 
 *
 */
Object * createObject(SDL_Surface * image, int subImage, int subImageNumber, objectType type, int x, int y, int w, int h);

/*  
 * 
 *
 * @param obj
 * @param x
 * @param y
 *
 */
void moveObject(Object * obj, int x, int y);

/*  
 * 
 *
 * @param obj
 * @param x
 * @param y
 *
 */
void positionObject(Object * obj, int x, int y);

/*  
 * 
 *
 * @param obj
 *
 */
void updateObjectAnimation(Object * obj);

/*  
 * 
 *
 * @param ship
 *
 */
void updateUserActions(Object * ship);

/*  
 * 
 *
 * @param bullets
 * @param image
 *
 * @return 
 *
 */
Object * updateUserBullets(Object * bullets, SDL_Surface * image);

/*  
 * 
 *
 * @param asteroids
 * @param image
 *
 * @return 
 *
 */
Object * updateAsteroids(Object * asteroids, SDL_Surface * image);

/*  
 * 
 *
 * @param obj
 *
 */
void freeObjects(Object * obj);

/*  
 * 
 *
 */
void setup();

/*  
 * 
 *
 * @param obj
 *
 * @return 
 *
 */
int countObjects(Object * obj);
#endif
