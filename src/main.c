/* Language Includes */
#ifndef __CSTD__
#define __CSTD__
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#endif

#ifndef __CSYSTEM__
#define __CSYSTEM__
#include <unistd.h>
#include <time.h>
#ifndef F_OK
#define F_OK 0
#endif
#endif

/* SDL Library */
#define SDL_MAIN_HANDLED
#include <SDL.h>

/* Local Includes */
#ifndef __TYPES__
#define __TYPES__
#include "types.h"
#endif

#ifndef __WRAPPERS__
#define __WRAPPERS__
#include "wrappers.h"
#endif

#ifndef __GAME__
#define __GAME__
#include "game.h"
#endif

#ifndef __GLOBAL__
#define __GLOBAL__
#include "global.h"
#endif

/* Environmental Dependancies */
#ifdef linux
#endif

#ifdef __APPLE__
#endif

#ifdef __WIN32
#include <windows.h>
#define sleep(x) Sleep(x*1000)
#endif

/* Define Global Variables */
uint16_t SCREEN_WIDTH;
uint16_t SCREEN_HEIGHT;
float SCREEN_TOP;
float SCREEN_BOTTOM;
float SCREEN_LEFT;
float SCREEN_RIGHT;
float FRAMES_PER_SECOND;
float GAME_TICK_RATIO;

float SHIP_SPEED;
float ASTEROID_SPEED;

/* Global SDL Variables */
SDL_Window * window;
SDL_Surface * screen;
const uint8_t * keystates;

int main(int argc, char * argv[])
{
    /* Game Variables */
    uint8_t exit       = 0;
    uint32_t  g_timer  = 0;

    /* SDL Variables */
    SDL_Surface * spriteSheet   = NULL;
    SDL_Event event;

    /* User Variables */
    Object * ship = NULL;

    /* NPC Variables */
    Object * asteroids = NULL;

    /* Setup Pre-Game Logic and Constants */
    setup();

    /* Initialize Window */
    if(!init("Star"))
    {
        return 0;
    }

    /* Load Bitmaps */
    spriteSheet = loadSurfaceBack(IMG_DIR "sprite-sheet.bmp", 0x0, 0x0, 0x0);

    /* Load User Object */
    ship = createObject(spriteSheet, 0, 3, SHIP, 0, 0, 32, 32);
    positionObject(ship, (SCREEN_WIDTH - SCREEN_RIGHT - 16) / 2, (SCREEN_HEIGHT - SCREEN_BOTTOM - 16));

    while(!exit)
    {
        /* Global Timer */
        g_timer = SDL_GetTicks();

        /* Clear Screen */
        clearScreen();

        /* SDL Events */
        while(SDL_PollEvent(&event) != 0)
        {
            if(event.type == SDL_QUIT)
            {
                exit = 1;
                break;
            }
            else if(event.type == SDL_KEYDOWN)
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        exit = 1;
                        break;
                }
            }
        }
        SDL_PumpEvents();

        /* Redraw Canvas, Update Window */
        asteroids = updateAsteroids(asteroids, spriteSheet);
        updateUserActions(ship);

        SDL_UpdateWindowSurface(window);

        /* Frames Per Second */
        delayFramesPerSecond(g_timer);
    }

    /* Clean Up */
    SDL_FreeSurface(spriteSheet);
    freeObjects(ship);
    freeObjects(asteroids);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
