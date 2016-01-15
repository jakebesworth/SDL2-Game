/* Includes */
#ifndef __CSTD__
#define __CSTD__
#include <stdlib.h>
#include <stdio.h>
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

/* Environmental Dependancies */
#ifdef linux
#endif

#ifdef __APPLE__
#endif

#ifdef __WIN32
#include <windows.h>
#define sleep(x) Sleep(x*1000)
#endif

/* SDL Library */
#define SDL_MAIN_HANDLED
#include <SDL.h>

/* File Constants */
#define IMG_DIR "assets/img/"
#define ERROR_FILE "logs/error_log"

/* Type Definitions */
typedef enum
{
    SHIP,
    ASTEROID_SMALL,
    ASTEROID_MEDIUM,
    ASTEROID_LARGE,
    WALL,
    TYPE_OBJECT_SIZE
} typeObject;

typedef struct object
{
    typeObject type;
    SDL_Surface * image;
    SDL_Rect clip;
    uint16_t subImage;
    uint16_t subImageNumber;
    int x;
    int y;
    struct object * next;
} Object;

/* SDL Wrapper Functions */
SDL_Surface * loadSurface(char * image);
SDL_Surface * loadSurfaceBack(char * image, uint8_t colourR, uint8_t colourG, uint8_t colourB);
void applySurface(int x, int y, SDL_Surface * source, SDL_Rect * clip);
int init(char * title);

/* Game Functions */
Object * createObject(SDL_Surface * image, int subImage, int subImageNumber, typeObject type, int x, int y, int w, int h);
void moveObject(Object * obj, int x, int y);
void positionObject(Object * obj, int x, int y);
void updateObjectAnimation(Object * obj);
void updateUserActions(Object * ship);
Object * updateAsteroids(Object * asteroids, SDL_Surface * image);
void freeObjects(Object * obj);

/* General Functions */
char * getDate();

/* Numeric Game Constants - Move to an options menu eventually */
#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 405
#define SCREEN_TOP (SCREEN_HEIGHT * 0.15)
#define SCREEN_BOTTOM 40
#define SCREEN_LEFT 5
#define SCREEN_RIGHT 40
#define FRAMES_PER_SECOND 60 /* Up to 144 */
#define GAME_TICK_RATIO (60.0 / FRAMES_PER_SECOND)

#define SHIP_SPEED (7.5 * GAME_TICK_RATIO)
#define ASTEROID_SPEED (1.5 * GAME_TICK_RATIO)

/* Global SDL Variables */
SDL_Window * window  = NULL;
SDL_Surface * screen = NULL;
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

    /* Setup*/
    freopen(ERROR_FILE, "a", stderr);
    srand(time(NULL));

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
        if(SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x0, 0x0, 0x0)))
        {
            fprintf(stderr, "[%s][%s: %d]Warning: Could not clear screen, error: %s\n", getDate(), __FILE__, __LINE__, SDL_GetError());
        }

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
        if((SDL_GetTicks() - g_timer) < (1000 / FRAMES_PER_SECOND))
        {
            SDL_Delay((1000 / FRAMES_PER_SECOND) - (SDL_GetTicks() - g_timer));
        }
    }

    /* Clean Up */
    SDL_FreeSurface(spriteSheet);
    freeObjects(ship);
    freeObjects(asteroids);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

Object * updateAsteroids(Object * asteroids, SDL_Surface * image)
{
    Object * asteroid;
    uint8_t random;

    if((rand() % 20) == 1)
    {
        random = rand() % 6;

        if(random >= 3)
        {
            asteroid = createObject(image, 0, 1, ASTEROID_SMALL, 0, 32, 32, 32);
        }
        else if(random >= 1)
        {
            asteroid = createObject(image, 0, 1, ASTEROID_MEDIUM, 32, 32, 64, 64);
        }
        else
        {
            asteroid = createObject(image, 0, 1, ASTEROID_LARGE, 96, 32, 96, 96);
        }

        asteroid->x = (int) ((rand() % (SCREEN_WIDTH)) - 32);
        asteroid->y = -96;

        asteroid->next = asteroids;
        asteroids = asteroid;
    }
    else
    {
        asteroid = asteroids;
    }

    while(asteroids != NULL)
    {
        if(asteroids->y < 0)
        {
//            freeObjects(asteroids);
        }

        moveObject(asteroids, 0, ASTEROID_SPEED);
        asteroids = asteroids->next;
    }

    return asteroid;
}

void updateUserActions(Object * ship)
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

void updateObjectAnimation(Object * obj)
{
    obj->subImage = ((obj->subImage + 1) >= obj->subImageNumber) ? 0 : obj->subImage++;
}

void positionObject(Object * obj, int x, int y)
{
    SDL_Rect clip = obj->clip;

    obj->x = x;
    obj->y = y;
    clip.x += clip.w * obj->subImage;
    applySurface(obj->x, obj->y, obj->image, &clip);
}

void moveObject(Object * obj, int x, int y)
{
    SDL_Rect clip = obj->clip;

    obj->x += x;
    obj->y += y;
    clip.x += clip.w * obj->subImage;
    applySurface(obj->x, obj->y, obj->image, &clip);
}

Object * createObject(SDL_Surface * image, int subImage, int subImageNumber, typeObject type, int x, int y, int w, int h)
{
    Object * obj = NULL;

    obj = malloc(sizeof(Object));

    if(obj == NULL)
    {
        fprintf(stderr, "[%s][%s: %d]Fatal Error: Memory allocation error\n", getDate(), __FILE__, __LINE__);
        exit(0);
    }

    obj->image = image;
    obj->subImage = subImage;
    obj->subImageNumber = 3;
    obj->x = obj->y = 0;
    obj->type = type;

    obj->clip.x = x;
    obj->clip.y = y;
    obj->clip.w = w;
    obj->clip.h = h;

    obj->next = NULL;

    return obj;
}

int init(char * title)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
       fprintf(stderr, "[%s][%s: %d]Fatal Error: SDL window init error: %s\n", getDate(), __FILE__, __LINE__, SDL_GetError());
       return 0;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(window == NULL)
    {
        fprintf(stderr, "[%s][%s: %d]Fatal Error: SDL window screen error: %s\n", getDate(), __FILE__, __LINE__, SDL_GetError());
        return 0;
    }

    screen = SDL_GetWindowSurface(window);

    if(screen == NULL)
    {
        fprintf(stderr, "[%s][%s: %d]Fatal Error: SDL screen can't get window surface error: %s\n", getDate(), __FILE__, __LINE__, SDL_GetError());
        return 0;
    }

    /* Initialize Window */
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x0, 0x0, 0x0));
    SDL_UpdateWindowSurface(window);

    /* Initialize Keystates */
    keystates = SDL_GetKeyboardState(NULL);

    return 1;
}

SDL_Surface * loadSurfaceBack(char * image, uint8_t colourR, uint8_t colourG, uint8_t colourB)
{
    int colorkey;
    SDL_Surface * opt = loadSurface(image);

    if(opt == NULL)
    {
        return NULL;
    }

    colorkey = SDL_MapRGB(opt->format, colourR, colourG, colourB);
    SDL_SetColorKey(opt, SDL_TRUE, colorkey);

    return opt;
}

/* TODO Look into SDL_BlitScaled  function */
SDL_Surface * loadSurface(char * image)
{
    SDL_Surface * opt  = NULL;
    SDL_Surface * load = NULL;

    if(screen == NULL)
    {
        fprintf(stderr, "[%s][%s: %d]Fatal Error: screen NULL\n", getDate(), __FILE__, __LINE__);
        exit(0);
    }

    if(strstr(image, "bmp") == NULL)
    {
        fprintf(stderr, "[%s][%s: %d]Warning: Images are not bitmap\n", getDate(), __FILE__, __LINE__);
        return NULL;
    }
    
    load = SDL_LoadBMP(image);

    if(load == NULL)
    {
        fprintf(stderr, "[%s][%s: %d]Warning: Could not load image %s, error: %s\n", getDate(), __FILE__, __LINE__, image, SDL_GetError());
    }
    else
    {
        opt = SDL_ConvertSurface(load, screen->format, NULL);
        if(opt == NULL)
        {
            fprintf(stderr, "[%s][%s: %d]Warning: Could not optimize image %s, error: %s\n", getDate(), __FILE__, __LINE__, image, SDL_GetError());
        }
    
        SDL_FreeSurface(load);
    }

    return opt; 
}

void applySurface(int x, int y, SDL_Surface * source, SDL_Rect * clip)
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(source, clip, screen, &offset);
}

char * getDate()
{
    char * date = NULL;
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    date = asctime(timeinfo);

    if(date[strlen(date)-1] == '\n')
    {
        date[strlen(date)-1] = '\0';
    }

    return date;
}

void freeObjects(Object * obj)
{
    while(obj != NULL)
    {
        free(obj);
        obj = obj->next;
    }
}
