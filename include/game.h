Object * createObject(SDL_Surface * image, int subImage, int subImageNumber, objectType type, int x, int y, int w, int h);
void moveObject(Object * obj, int x, int y);
void positionObject(Object * obj, int x, int y);
void updateObjectAnimation(Object * obj);
void updateUserActions(Object * ship);
Object * updateAsteroids(Object * asteroids, SDL_Surface * image);
void freeObjects(Object * obj);
void setup();
