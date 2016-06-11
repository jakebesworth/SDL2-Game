/* Standard Includes */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* SDL Library */
#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#include <SDL.h>

/* Local Includes */
#include "types.h"
#include "wrappers.h"
#include "object.h"
#include "game.h"
#include "global.h"
#include "display.h"
#include "extern.h"

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
GlobalSDL * Global;

float SHIP_SPEED;
float ASTEROID_SPEED;
float BULLET_TINY_SPEED;

uint32_t score; 

int main(int argc, char * argv[])
{
    /* SDL Variables */
    SDL_Texture * spriteSheet = NULL;
    SDL_Texture * fontLarge = NULL;
    SDL_Event event;

    /* User Variables */
    Object * ship = NULL;
    Object * bullets = NULL;

    /* NPC Variables */
    Object * asteroids = NULL;

    /* Setup Pre-Game Logic and Constants */
    startSDL();

    /* Load Bitmaps */
    spriteSheet = loadTextureBack(getAbsolutePath(IMG_DIR "sprite-sheet.bmp"), 0x0, 0x0, 0x0);
    fontLarge = loadTextureBack(getAbsolutePath(FONT_DIR "fontx64.bmp"), 0x0, 0x0, 0x0);

    /* Load User Objects */
    ship = createObject(spriteSheet, 0, 3, SHIP, 3, 0, 0, 32, 32, 1.0);
    positionObject(ship, ((Global->screenWidth - Global->screenRight) / 2 + (ship->clip.w / 2)) + Global->screenLeft, ((Global->screenHeight - Global->screenTop) * 0.75 + (ship->clip.h / 2)) + Global->screenBottom);
    Global->timer[BULLET_TINY_TIMER] = SDL_GetTicks();

    while(!Global->exit)
    {
        /* Global Timer */
        Global->timer[GLOBAL_TIMER] = SDL_GetTicks();

        /* Clear Screen */
        clearScreen();

        /* SDL Events */
        while(SDL_PollEvent(&event) != 0)
        {
            if(event.type == SDL_QUIT)
            {
                Global->exit = 1;
                break;
            }
            else if(event.type == SDL_KEYDOWN)
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_p:
                        Global->state = (Global->state == DEFAULT ? PAUSE : DEFAULT);
                        break;
                    case SDLK_ESCAPE:
                        Global->exit = 1;
                        break;
                }
            }
        }

        /* Load Event Stack */
        SDL_PumpEvents();

        /* Have a function to update all timers */
        Global->timer[DISPLAY_GAME_TIMER] = SDL_GetTicks() / 1000;

        /* Default game state, player playing the game */
        if(Global->state == DEFAULT)
        {
            if(ship->lives <= 0)
            {
                Global->exit = 1;
                continue;
            }

            bullets = updateUserActions(ship, bullets, spriteSheet, Global->timer);
            asteroids = updateAsteroids(asteroids, spriteSheet);
            updateObjectCollision(&ship, &bullets, &asteroids);
            displayHUD(ship, fontLarge, Global->timer[DISPLAY_GAME_TIMER]);
        }
        /* Game Paused */
        else if(Global->state == PAUSE)
        {
            displayTextMiddle(fontLarge, "Pause", FONT_LARGE, 1.0);
            displayHUD(ship, fontLarge, Global->timer[DISPLAY_GAME_TIMER]);
        }
        /* Introduction to new waves */
        else if(Global->state == MENU)
        {

        }

        /* Redraw Window */
        updateWindow();

        /* Frames Per Second Delay */
        delayFramesPerSecond(Global->timer[GLOBAL_TIMER]);
    }

    /* Game Over */
    if(ship->lives <= 0)
    {
        displayGameOver(fontLarge);
    }

    /* Clean Up - TODO better way to handle these objects in main*/
    SDL_DestroyTexture(spriteSheet);
    SDL_DestroyTexture(fontLarge);
    freeObjects(ship);
    freeObjects(asteroids);
    freeObjects(bullets);

    /* Close SDL framework */
    endSDL();

    return 0;
}
