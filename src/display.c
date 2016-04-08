/* Language Includes */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* SDL Library */
#include <SDL.h>

/* Local Includes */
#include "types.h"
#include "global.h"
#include "object.h"
#include "wrappers.h"
#include "display.h"
#include "extern.h"

void displayGameOver(SDL_Texture * font)
{
    clearScreen();
    displayTextMiddle(font, "game over", FONT_SMALL);
    updateWindow();
    SDL_Delay(2 * 1000);
}

void displayTextMiddle(SDL_Texture * font, char * text, objectType type)
{
    Object * temp = createTextObject(font, text, type);

    positionTextObject(temp, (SCREEN_WIDTH - (strlen(text) * temp->clip.w)) / 2, (SCREEN_HEIGHT - SCREEN_BOTTOM - 16) / 2);
    freeObjects(temp);
}
            
void displayHUD(Object * ship, SDL_Texture * font, uint32_t timer)
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
    temp = createTextObject(font, buffer, FONT_SMALL);

    positionTextObject(temp, 0, 0);

    /* Display score number */
    previous = (temp->x + (countObjects(temp) * temp->clip.w));
    freeObjects(temp);
    snprintf(buffer, BUFFER_SIZE, "%d", score);
    temp = createTextObject(font, buffer, FONT_SMALL);

    positionTextObject(temp, previous, 0);
    freeObjects(temp);

    /* Display lives text */
    strncpy(buffer, "lives", BUFFER_SIZE);
    temp = createTextObject(font, buffer, FONT_SMALL);

    positionTextObject(temp, ((SCREEN_WIDTH / 4)), 0);

    /* Display lives number */
    previous = (temp->x + (countObjects(temp) * temp->clip.w));
    freeObjects(temp);
    snprintf(buffer, BUFFER_SIZE, "%d", ship->lives);
    temp = createTextObject(font, buffer, FONT_SMALL);

    positionTextObject(temp, previous, 0);    
    freeObjects(temp);

    /* Display Timer */
    snprintf(buffer, BUFFER_SIZE, "%d", timer);
    temp = createTextObject(font, buffer, FONT_SMALL);

    positionTextObject(temp, ((SCREEN_WIDTH - (countObjects(temp) * temp->clip.w))), 0);
    freeObjects(temp);
}
