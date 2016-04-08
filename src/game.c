/* Language Includes */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* Standard System Include */
#include <unistd.h>
#include <time.h>

#ifndef F_OK
#define F_OK 0
#endif

/* SDL Library */
#include <SDL.h>

/* Local Includes */
#include "types.h"
#include "wrappers.h"
#include "object.h"
#include "game.h"
#include "global.h"
#include "extern.h"

void setup()
{
#ifdef ERROR_FILE
    /* Specifically to avoid return warnings and unused variable warnings */
    FILE * temp = freopen(ERROR_FILE, "a", stderr);
    (void)temp;
#endif

    /* Initialize Random Seed */
    srand(time(NULL));
    
    /* Initialize Keystates */
    keystates = SDL_GetKeyboardState(NULL);

    /* Constant Logic / initialize */
    SCREEN_WIDTH = 1920;
    SCREEN_HEIGHT = 1080;
    SCREEN_TOP = 64;
    SCREEN_BOTTOM = 40;
    SCREEN_LEFT = 5;
    SCREEN_RIGHT = 40;
    FRAMES_PER_SECOND = 60.0; /* Up to 144 */
    GAME_TICK_RATIO = (60.0 / FRAMES_PER_SECOND);

    SHIP_SPEED = (7.5 * GAME_TICK_RATIO);
    ASTEROID_SPEED = (1.5 * GAME_TICK_RATIO);
    BULLET_TINY_SPEED = (9.0 * GAME_TICK_RATIO);

    /* Global Score */
    score = 0;

    /* Initialize Window */
    if(!init("Star"))
    {
        exit(0);
    }
}

void updateObjectCollision(Object ** ship, Object ** bullets, Object ** asteroids)
{
    Object * asteroidsRoot = *asteroids;
    Object * bulletsRoot;

    while(asteroidsRoot != NULL)
    {
        bulletsRoot = *bullets;

        if(objectCollision(asteroidsRoot, *ship))
        {
            (*ship)->lives--;
            asteroidsRoot->lives = 0;
        }

        while(bulletsRoot != NULL)
        {
            if(objectCollision(asteroidsRoot, bulletsRoot))
            {
                asteroidsRoot->lives--;
                bulletsRoot->lives = 0;

                if(asteroidsRoot->lives <= 0)
                {
                    if(asteroidsRoot->type == ASTEROID_SMALL)
                    {
                        score += 1;
                    }
                    else if(asteroidsRoot->type == ASTEROID_MEDIUM)
                    {
                        score += 2;
                    }
                    else if(asteroidsRoot->type == ASTEROID_LARGE)
                    {
                        score += 3;
                    }
                }
                else
                {
                    if(bulletsRoot->type == BULLET_TINY)
                    {
                        score++;
                    }
                }
            }

            bulletsRoot = bulletsRoot->next;
        }

        asteroidsRoot = asteroidsRoot->next;
    }
}

Object * updateAsteroids(Object * asteroids, SDL_Texture * image)
{
    Object * asteroidsRoot;
    Object * asteroid;
    Object * previousAsteroid;
    uint8_t random;
    uint8_t root = 1;

    if((rand() % 20) == 1)
    {
        random = rand() % 6;

        if(random >= 3)
        {
            asteroid = createObject(image, 0, 1, ASTEROID_SMALL, 1, 0, 32, 32, 32);
        }
        else if(random >= 1)
        {
            asteroid = createObject(image, 0, 1, ASTEROID_MEDIUM, 3, 32, 32, 64, 64);
        }
        else
        {
            asteroid = createObject(image, 0, 1, ASTEROID_LARGE, 6, 96, 32, 96, 96);
        }

        asteroid->x = (int) ((rand() % (SCREEN_WIDTH)) - (asteroid->clip.w / 2));
        asteroid->y = -(asteroid->clip.h);

        asteroid->next = asteroids;
        asteroids = asteroid;
    }

    asteroidsRoot = asteroids;

    while(asteroids != NULL)
    {
        if(asteroids->y > (SCREEN_HEIGHT + asteroids->clip.h) || asteroids->lives <= 0)
        {
            asteroid = asteroids;
            asteroids = asteroids->next;

            if(root)
            {
                asteroidsRoot = asteroids;
            }
            else
            {
                previousAsteroid->next = asteroids;
            }

            asteroid->next = NULL;
            freeObjects(asteroid);
            continue;
        }

        previousAsteroid = asteroids;

        moveObject(asteroids, 0, ASTEROID_SPEED);
        asteroids = asteroids->next;

        if(root)
        {
            root = 0;
        }
    }

    return asteroidsRoot;
}

Object * updateUserBullets(Object * ship, Object * bullets, SDL_Texture * image, uint32_t * timer)
{
    Object * bulletsRoot;
    Object * bullet;
    Object * previousBullet;
    uint8_t root = 1;

    if(timer[BULLET_TINY_TIMER] < SDL_GetTicks())
    {
        if(keystates[SDL_SCANCODE_1] || keystates[SDL_SCANCODE_SPACE])
        {
            bullet = createObject(image, 0, 2, BULLET_TINY, 1, 0, 144, 16, 16);

            bullet->x = (ship->x + (bullet->clip.w / 2));
            bullet->y = (ship->y - (bullet->clip.w / 2));

            bullet->next = bullets;
            bullets = bullet;

            timer[BULLET_TINY_TIMER] = (SDL_GetTicks() + 150);
        }
    }

    bulletsRoot = bullets;

    while(bullets != NULL)
    {
        if(bullets->y <= SCREEN_TOP || bullets->lives <= 0)
        {
            bullet = bullets;
            bullets = bullets->next;

            if(root)
            {
                bulletsRoot = bullets;
            }
            else
            {
                previousBullet->next = bullets;
            }

            bullet->next = NULL;
            freeObjects(bullet);
            continue;
        }

        previousBullet = bullets;

        moveObject(bullets, 0, (-1 * BULLET_TINY_SPEED));
        bullets = bullets->next;

        if(root)
        {
            root = 0;
        }
    }

    return bulletsRoot;
}

void updateUserShipMovement(Object * ship)
{
    int8_t shipX = 0;
    int8_t shipY = 0;

    /* User Keyboard  */
    if(keystates[SDL_SCANCODE_LEFT] || keystates[SDL_SCANCODE_A])
    {
        shipX--;
    }

    if(keystates[SDL_SCANCODE_RIGHT] || keystates[SDL_SCANCODE_D])
    {
        shipX++;
    }

    if(keystates[SDL_SCANCODE_UP] || keystates[SDL_SCANCODE_W])
    {
        shipY--;
    }

    if(keystates[SDL_SCANCODE_DOWN] || keystates[SDL_SCANCODE_S])
    {
        shipY++;
    }

    /* Updating Ship Animation */
    if(shipX == 0)
    {
        ship->subImage = 0;
    }    
    else if(shipX == -1)
    {
        ship->subImage = 1;
    }
    else if(shipX == 1)
    {
        ship->subImage = 2;
    }

    /* Setting Ship Boundaries */
    if((ship->x + (shipX * SHIP_SPEED)) < (0 + SCREEN_LEFT))
    {
        shipX = 0;
    }

    if((ship->x + (shipX * SHIP_SPEED)) > (SCREEN_WIDTH - SCREEN_RIGHT))
    {
        shipX = 0;
    }

    if((ship->y + (shipY * SHIP_SPEED)) < (0 + SCREEN_TOP))
    {
        shipY = 0;
    }

    if((ship->y + (shipY * SHIP_SPEED)) > (SCREEN_HEIGHT - SCREEN_BOTTOM))
    {
        shipY = 0;
    }

    moveObject(ship, shipX * SHIP_SPEED, shipY * SHIP_SPEED);
}

Object * updateUserActions(Object * ship, Object * bullets, SDL_Texture * image, uint32_t * timer)
{
    updateUserShipMovement(ship);
    return updateUserBullets(ship, bullets, image, timer);
}

void updateObjectAnimation(Object * obj)
{
    obj->subImage = ((obj->subImage + 1) >= obj->subImageNumber) ? 0 : (obj->subImage + 1);
}
