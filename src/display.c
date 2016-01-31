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
#include "types.h"
#include "global.h"
#include "object.h"
#include "display.h"
            
void displayHUD(Object * ship, SDL_Texture * font)
{
    Object * temp;
    char buffer[BUFFER_SIZE] = {0};
    int previous = 0;
    SDL_Rect bar;

    /* Set the HUD bar */
    bar.x = 0;
    bar.y = 0;
    bar.w = SCREEN_WIDTH;
    bar.h = SCREEN_TOP;

    SDL_RenderFillRect(renderer, &bar);

    /* Display score text */
    strncpy(buffer, "score", BUFFER_SIZE);
    temp = createTextObject(font, buffer, FONT_TINY);

    positionTextObject(temp, 0, 0);

    /* Display score number */
    previous = (temp->x + (countObjects(temp) * temp->clip.w));
    freeObjects(temp);
    snprintf(buffer, BUFFER_SIZE, "%d", score);
    temp = createTextObject(font, buffer, FONT_TINY);

    positionTextObject(temp, previous, 0);
    freeObjects(temp);

    /* Display lives text */
    strncpy(buffer, "lives", BUFFER_SIZE);
    temp = createTextObject(font, buffer, FONT_TINY);

    positionTextObject(temp, ((SCREEN_WIDTH / 4)), 0);

    /* Display lives number */
    previous = (temp->x + (countObjects(temp) * temp->clip.w));
    freeObjects(temp);
    snprintf(buffer, BUFFER_SIZE, "%d", ship->lives);
    temp = createTextObject(font, buffer, FONT_TINY);

    positionTextObject(temp, previous, 0);    
    freeObjects(temp);
}
