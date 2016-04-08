/* Language Includes */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* SDL Library */
#include <SDL.h>

/* Local Includes */
#include "wrappers.h"
#include "extern.h"
#include "global.h"

int init(char * title)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
       fprintf(stderr, "[%s][%s: %d]Fatal Error: SDL window init error: %s\n", getDate(), __FILE__, __LINE__, SDL_GetError());
       return 0;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP); /* SDL_WINDOW_SHOWN */

    if(window == NULL)
    {
        fprintf(stderr, "[%s][%s: %d]Fatal Error: SDL window error: %s\n", getDate(), __FILE__, __LINE__, SDL_GetError());
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
        SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
    }

    SDL_ShowCursor(SDL_DISABLE);

    /* Initialize Window */
    updateWindow();

    return 1;
}

SDL_Texture * loadTexture(char * image, SDL_Surface * surface)
{
    SDL_Texture * texture = NULL;

    if(surface == NULL)
    {
        if(image == NULL)
        {
            fprintf(stderr, "[%s][%s: %d]Warning: image string NULL\n", getDate(), __FILE__, __LINE__);
            return NULL;

        }

        if(strstr(image, "bmp") == NULL)
        {
            fprintf(stderr, "[%s][%s: %d]Warning: Images are not bitmap\n", getDate(), __FILE__, __LINE__);
            return NULL;
        }

        surface = SDL_LoadBMP(image);

        if(surface == NULL)
        {
            fprintf(stderr, "[%s][%s: %d]Warning: Could not load image %s into surface, error: %s\n", getDate(), __FILE__, __LINE__, image, SDL_GetError());
            return NULL;
        }
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);

    if(texture == NULL)
    {
        fprintf(stderr, "[%s][%s: %d]Warning: Could not create texture %s, error: %s\n", getDate(), __FILE__, __LINE__, image, SDL_GetError());
    }

    SDL_FreeSurface(surface);

    return texture;
}

SDL_Texture * loadTextureBack(char * image, uint8_t colourR, uint8_t colourG, uint8_t colourB)
{
    SDL_Texture * texture = NULL;
    SDL_Surface * surface = NULL;

    surface = SDL_LoadBMP(image);

    if(surface == NULL)
    {
        fprintf(stderr, "[%s][%s: %d]Warning: Could not load image %s into surface, error: %s\n", getDate(), __FILE__, __LINE__, image, SDL_GetError());
        return NULL;
    }

    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, colourR, colourG, colourB));

    texture = loadTexture(image, surface);

    if(texture == NULL)
    {
        fprintf(stderr, "[%s][%s: %d]Warning: Could not create textureBack %s, error: %s\n", getDate(), __FILE__, __LINE__, image, SDL_GetError());
    }

    return texture;
}

void applyTexture(int x, int y, SDL_Texture * source, SDL_Rect * clip)
{
    SDL_Rect offset = *clip;

    offset.x = x;
    offset.y = y;

    if(SDL_RenderCopy(renderer, source, clip, &offset))
    {
        fprintf(stderr, "[%s][%s: %d]Warning: Could not render copy, error: %s\n", getDate(), __FILE__, __LINE__, SDL_GetError());
    }
}

void setTextureAlpha(SDL_Texture * texture, uint8_t alpha)
{
    if(SDL_SetTextureAlphaMod(texture, alpha))
    {
        fprintf(stderr, "[%s][%s: %d]Warning: Could not set texture alpha mod, error: %s\n", getDate(), __FILE__, __LINE__, SDL_GetError());
    }
}

void updateWindow()
{
    SDL_RenderPresent(renderer);
}

void delayFramesPerSecond(uint32_t timer)
{
    if((SDL_GetTicks() - timer) < (1000 / FRAMES_PER_SECOND))
    {
        SDL_Delay((1000 / FRAMES_PER_SECOND) - (SDL_GetTicks() - timer));
    }
}

char * getAbsolutePath(char * relativeString)
{
    static char absoluteString[BUFFER_SIZE] = {0};
    char * basePathString = NULL;

    if(relativeString == NULL)
    {
        fprintf(stderr, "[%s][%s: %d]Warning: relative string NULL\n", getDate(), __FILE__, __LINE__);
        return NULL;
    }

    basePathString = SDL_GetBasePath();

    if(basePathString == NULL)
    {
        fprintf(stderr, "[%s][%s: %d]Warning: Could not get SDL Basepath String, error: %s\n", getDate(), __FILE__, __LINE__, SDL_GetError());
        return NULL;
    }

    (void)strcpy(absoluteString, basePathString);
    SDL_free(basePathString);
    (void)strcat(absoluteString, relativeString);

    return absoluteString;
}

void clearScreen()
{
    if(SDL_RenderClear(renderer))
    {
        fprintf(stderr, "[%s][%s: %d]Warning: Could not clear screen renderer, error: %s\n", getDate(), __FILE__, __LINE__, SDL_GetError());
    }
}
