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
    displayTextMiddle(font, "Game Over", FONT_LARGE);
    updateWindow();
    SDL_Delay(2 * 1000);
}

void displayTextMiddle(SDL_Texture * font, char * text, objectType type)
{
    Object * temp = createTextObject(font, text, type);

    positionTextObject(temp, (Global->screenWidth - Global->screenRight + Global->screenLeft - ((strlen(text) * temp->clip.w) / 2)) / 2, (Global->screenHeight - Global->screenBottom + Global->screenTop - (temp->clip.h / 2)) / 2);
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
    bar.w = Global->screenWidth;
    bar.h = Global->screenTop;

    SDL_RenderFillRect(Global->renderer, &bar);

    /* Display score text */
    strncpy(buffer, "Score", BUFFER_SIZE);
    temp = createTextObject(font, buffer, FONT_LARGE);

    positionTextObject(temp, 0, 0);

    /* Display score number */
    previous = (temp->x + (countObjects(temp) * temp->clip.w));
    freeObjects(temp);
    snprintf(buffer, BUFFER_SIZE, "%d", score);
    temp = createTextObject(font, buffer, FONT_LARGE);

    positionTextObject(temp, previous, 0);
    freeObjects(temp);

    /* Display lives text */
    strncpy(buffer, "Lives", BUFFER_SIZE);
    temp = createTextObject(font, buffer, FONT_LARGE);

    positionTextObject(temp, ((Global->screenWidth / 4)), 0);

    /* Display lives number */
    previous = (temp->x + (countObjects(temp) * temp->clip.w));
    freeObjects(temp);
    snprintf(buffer, BUFFER_SIZE, "%d", ship->lives);
    temp = createTextObject(font, buffer, FONT_LARGE);

    positionTextObject(temp, previous, 0);    
    freeObjects(temp);

    /* Display Timer */
    snprintf(buffer, BUFFER_SIZE, "%d", timer);
    temp = createTextObject(font, buffer, FONT_LARGE);

    positionTextObject(temp, ((Global->screenWidth - (countObjects(temp) * temp->clip.w))), 0);
    freeObjects(temp);
}
