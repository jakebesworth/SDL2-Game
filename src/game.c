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

void endSDL()
{

    SDL_free(Global->basePath);
    SDL_DestroyRenderer(Global->renderer);
    SDL_DestroyWindow(Global->window);

    free(Global);
    SDL_Quit();
}

void startSDL()
{
    /* Global game object */
    Global = calloc(1, sizeof(GlobalSDL));

    if(Global == NULL)
    {
        fprintf(stderr, "[%s][%s: %d]Fatal Error: Memory c-allocation error\n", getDate(), __FILE__, __LINE__);
        exit(0);
    }

    Global->basePath = SDL_GetBasePath();

    if(Global->basePath == NULL)
    {
        fprintf(stderr, "[%s][%s: %d]Fatal Error: Could not get SDL Basepath String, error: %s\n", getDate(), __FILE__, __LINE__, SDL_GetError());
        exit(0);
    }

    if(freopen(getAbsolutePath(ERROR_FILE), "a", stderr) == NULL)
    {
       fprintf(stderr, "[%s][%s: %d]Warning: Freopen could not pipe stream\n", getDate(), __FILE__, __LINE__);
    }

    /* Initialize Random Seed */
    srand(time(NULL));

    Global->window = NULL;
    Global->renderer = NULL;

    /* Initialize Window */
    if(!initSDL("Naquadah Asteroids"))
    {
        exit(0);
    }

    setWindowIcon(getAbsolutePath(IMG_DIR "icon.bmp"));

    /* Constant Logic / initialize */
    Global->screenWidth = 1920; //getNativeWidth();
    Global->screenHeight = 1080; //getNativeHeight();
    Global->screenTop = 64;
    Global->screenBottom = 5;
    Global->screenLeft = 5;
    Global->screenRight = 5;
    /* Make this an option */
    Global->framesPerSecond = 60.0;
    Global->gameTickRatio = (60.0 / Global->framesPerSecond);

    /* Initialize Keystates */
    Global->keystates = SDL_GetKeyboardState(NULL);

    Global->exit = 0;
    Global->state = DEFAULT;

    SHIP_SPEED = (7.5 * Global->gameTickRatio);
    ASTEROID_SPEED = (1.5 * Global->gameTickRatio);
    BULLET_TINY_SPEED = (9.0 * Global->gameTickRatio);

    /* Global Score */
    score = 0;
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

    ASTEROID_SPEED *= (ASTEROID_SPEED < SHIP_SPEED * 2) ? 1.00025 : 1;

    if((rand() % (int) (30 / ((ASTEROID_SPEED < 30) ? ASTEROID_SPEED : 30))) == 0)
    {
        random = rand() % 6;

        if(random >= 3)
        {
            asteroid = createObject(image, 0, 1, ASTEROID_SMALL, 1, 0, 32, 32, 32, 1.0);
        }
        else if(random >= 1)
        {
            asteroid = createObject(image, 0, 1, ASTEROID_MEDIUM, 3, 32, 32, 64, 64, 1.0);
        }
        else
        {
            asteroid = createObject(image, 0, 1, ASTEROID_LARGE, 6, 96, 32, 96, 96, 1.0);
        }

        asteroid->x = (int) ((rand() % (Global->screenWidth)) - (asteroid->clip.w / 2));
        asteroid->y = -(asteroid->clip.h);

        asteroid->next = asteroids;
        asteroids = asteroid;
    }

    asteroidsRoot = asteroids;

    while(asteroids != NULL)
    {
        if(asteroids->y > (Global->screenHeight + asteroids->clip.h) || asteroids->lives <= 0)
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
        if(Global->keystates[SDL_SCANCODE_1] || Global->keystates[SDL_SCANCODE_SPACE])
        {
            bullet = createObject(image, 0, 2, BULLET_TINY, 1, 0, 144, 16, 16, 1.0);

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
        if(bullets->y <= Global->screenTop || bullets->lives <= 0)
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
    int temp = 0;

    /* User Keyboard  */
    if(Global->keystates[SDL_SCANCODE_LEFT] || Global->keystates[SDL_SCANCODE_A])
    {
        shipX--;
    }

    if(Global->keystates[SDL_SCANCODE_RIGHT] || Global->keystates[SDL_SCANCODE_D])
    {
        shipX++;
    }

    if(Global->keystates[SDL_SCANCODE_UP] || Global->keystates[SDL_SCANCODE_W])
    {
        shipY--;
    }

    if(Global->keystates[SDL_SCANCODE_DOWN] || Global->keystates[SDL_SCANCODE_S])
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

    shipX *= SHIP_SPEED;
    shipY *= SHIP_SPEED;

    /* Setting Ship Boundaries */
    if((ship->x + shipX) < Global->screenLeft)
    {
        temp = (Global->screenLeft - ship->x);
        shipX = temp > 0 ? temp : 0;
    }

    if((ship->x + ship->clip.w + shipX) > (Global->screenWidth - Global->screenRight))
    {
       temp = ((Global->screenWidth - Global->screenRight) - ship->x - ship->clip.w);
       shipX = temp > 0 ? temp : 0;
    }

    if((ship->y + shipY) < Global->screenTop)
    {
        temp = (Global->screenTop - ship->y);
        shipY =  temp > 0 ? temp : 0;
    }

    if((ship->y + ship->clip.h + shipY) > (Global->screenHeight - Global->screenBottom))
    {
        temp = ((Global->screenHeight - Global->screenBottom) - ship->y - ship->clip.h);
        shipY = temp > 0 ? temp : 0;
    }

    moveObject(ship, shipX, shipY);
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
