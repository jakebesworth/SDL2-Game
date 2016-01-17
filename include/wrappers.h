SDL_Surface * loadSurface(char * image);
SDL_Surface * loadSurfaceBack(char * image, uint8_t colourR, uint8_t colourG, uint8_t colourB);
void applySurface(int x, int y, SDL_Surface * source, SDL_Rect * clip);
int init(char * title);
void clearScreen();
void delayFramesPerSecond(uint32_t timer);
