/* Language Includes */
#ifndef CSTD_
#define CSTD_
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#endif

/* SDL Library */
#ifndef SDL_
#define SDL_
#include <SDL.h>
#endif

/* Local Includes */
#include "wrappers.h"
#include "global.h"

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

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == NULL)
    {
        fprintf(stderr, "[%s][%s: %d]Fatal Error: SDL Renderer error: %s\n", getDate(), __FILE__, __LINE__, SDL_GetError());
        return 0;
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
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
        opt = SDL_ConvertSurface(load, screen->format, 0);
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

void updateWindow()
{
    if(SDL_UpdateWindowSurface(window))
    {
        fprintf(stderr, "[%s][%s: %d]Warning: Could not update window surface, error: %s\n", getDate(), __FILE__, __LINE__, SDL_GetError());
    }
}

void delayFramesPerSecond(uint32_t timer)
{
    if((SDL_GetTicks() - timer) < (1000 / FRAMES_PER_SECOND))
    {
        SDL_Delay((1000 / FRAMES_PER_SECOND) - (SDL_GetTicks() - timer));
    }
}

void clearScreen()
{
    if(SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x0, 0x0, 0x0)))
    {
        fprintf(stderr, "[%s][%s: %d]Warning: Could not clear screen, error: %s\n", getDate(), __FILE__, __LINE__, SDL_GetError());
    }
}
