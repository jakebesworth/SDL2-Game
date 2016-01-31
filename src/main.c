/* Language Includes */
#ifndef CSTD_
#define CSTD_
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#endif

#ifndef CSYSTEM_
#define CSYSTEM_
#include <unistd.h>
#include <time.h>
#ifndef F_OK
#define F_OK 0
#endif
#endif

/* SDL Library */
#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#ifndef SDL_
#define SDL_
#include <SDL.h>
#endif

/* Local Includes */
#include "types.h"
#include "wrappers.h"
#include "object.h"
#include "game.h"
#include "global.h"
#include "display.h"

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
float BULLET_TINY_SPEED;

/* Global SDL Variables */
SDL_Window * window;
SDL_Renderer * renderer;
const uint8_t * keystates;
uint32_t score; 

int main(int argc, char * argv[])
{
    /* Game Variables */
    uint8_t exit       = 0;
    uint32_t g_timer   = 0;
    gameState g_state  = DEFAULT;
    Object * pause = NULL;

    /* SDL Variables */
    SDL_Texture * spriteSheet = NULL;
    SDL_Texture * fontTiny = NULL;
    SDL_Texture * fontSmall = NULL;
    SDL_Event event;

    /* User Variables */
    Object * ship = NULL;
    Object * bullets = NULL;
    uint32_t userTimer[TIMER_TYPE_SIZE] = {0};

    /* NPC Variables */
    Object * asteroids = NULL;

    /* Setup Pre-Game Logic and Constants */
    setup();

    /* Load Bitmaps */
    spriteSheet = loadTextureBack(IMG_DIR "sprite-sheet.bmp", 0x0, 0x0, 0x0);
    fontTiny = loadTextureBack(FONT_DIR "font-tiny.bmp", 0x0, 0x0, 0x0);
    fontSmall = loadTextureBack(FONT_DIR "font-small.bmp", 0x0, 0x0, 0x0);
    pause = createTextObject(fontSmall, "pause", FONT_SMALL);

    /* Load User Objects */
    ship = createObject(spriteSheet, 0, 3, SHIP, 3, 0, 0, 32, 32);
    positionObject(ship, (SCREEN_WIDTH - SCREEN_RIGHT - 16) / 2, (SCREEN_HEIGHT - SCREEN_BOTTOM - 16));
    userTimer[BULLET_TINY_TIMER] = SDL_GetTicks();

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
                    case SDLK_p:
                        g_state = (g_state == DEFAULT ? PAUSE : DEFAULT);
                        break;
                    case SDLK_ESCAPE:
                        exit = 1;
                        break;
                }
            }
        }

        /* Load Event Stack */
        SDL_PumpEvents();

        /* Default game state, player playing the game */
        if(g_state == DEFAULT)
        {
            bullets = updateUserActions(ship, bullets, spriteSheet, userTimer);
            asteroids = updateAsteroids(asteroids, spriteSheet);
            updateObjectCollision(&ship, &bullets, &asteroids);
            displayHUD(ship, fontTiny);
        }
        /* Game Paused */
        else if(g_state == PAUSE)
        {
            positionTextObject(pause, (SCREEN_WIDTH - SCREEN_RIGHT - 160) / 2, (SCREEN_HEIGHT - SCREEN_BOTTOM - 16) / 2);
        }
        /* Introduction to new waves */
        else if(g_state == WAVE)
        {

        }

        /* Redraw Window */
        updateWindow();

        /* Frames Per Second Delay */
        delayFramesPerSecond(g_timer);
    }

    /* Clean Up - think of a better way to do this*/
    SDL_DestroyTexture(spriteSheet);
    SDL_DestroyTexture(fontSmall);
    SDL_DestroyTexture(fontTiny);
    freeObjects(ship);
    freeObjects(pause);
    freeObjects(asteroids);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
