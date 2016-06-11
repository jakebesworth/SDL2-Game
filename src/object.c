/* Language Includes */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* SDL Library */
#include <SDL.h>

/* Local Includes */
#include "types.h"
#include "wrappers.h"
#include "object.h"
#include "global.h"

float getTextObjectLength(Object * obj, int extra)
{
    return (obj == NULL ? 0 : ((countObjects(obj) + extra) * obj->clip.w * 0.5 * obj->scale));
}

int objectCollision(Object * obj1, Object * obj2)
{
    if(((obj1->x + (obj1->clip.w * obj1->scale)) >= obj2->x) && ((obj1->y + (obj1->clip.h * obj1->scale)) >= obj2->y) && ((obj2->x + (obj2->clip.w * obj2->scale)) >= obj1->x) && ((obj2->y + (obj2->clip.h * obj2->scale)) >= obj1->y))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void setObjectAlpha(Object * obj, uint8_t alpha)
{
    while(obj != NULL)
    {
        setTextureAlpha(obj->image, alpha);
        obj = obj->next;
    }
}

Object * createTextObject(SDL_Texture * image, char * text, objectType type, float scale)
{
    int i;
    Object * obj = NULL;
    Object * objRoot = NULL;
    uint16_t width = 0;
    uint16_t height = 0;
    int textLength = strlen(text);

    if(type == FONT_TINY)
    {
        width = height = 16;
    }
    else if(type == FONT_SMALL)
    {
        width = height = 32;
    }
    else if(type == FONT_MEDIUM)
    {
        width = height = 48;
    }
    else if(type == FONT_LARGE)
    {
        width = height = 64;
    }

    for(i = 0; i < textLength; i++)
    {
        if(i == 0)
        {
            obj = createObject(image, 0, 1, type, 1, (getTextX(text[i]) * width), (getTextY(text[i]) * height), width, height, scale);
            objRoot = obj;
        }
        else
        {
            obj->next = createObject(image, 0, 1, type, 1, (getTextX(text[i]) * width), (getTextY(text[i]) * height), width, height, scale);
            obj = obj->next;
        }
    }

    return objRoot;
}

int getTextX(char c)
{
    if(c <= 43)
    {
        return (c - 32);
    }
    else if(c <= 55)
    {
        return (c - 44);
    } 
    else if(c <= 67)
    {
        return (c - 56);
    }
    else if(c <= 79)
    {
        return (c - 68);
    }
    else if(c <= 91)
    {
        return (c - 80);
    }
    else if(c <= 103)
    {
        return (c - 92);
    }
    else if(c <= 115)
    {
        return (c - 104);
    }
    else
    {
        return (c - 116);
    }
}

int getTextY(char c)
{
    if(c <= 43)
    {
        return 0;
    }
    else if(c <= 55)
    {
        return 1;
    } 
    else if(c <= 67)
    {
        return 2;
    }
    else if(c <= 79)
    {
        return 3;
    }
    else if(c <= 91)
    {
        return 4;
    }
    else if(c <= 103)
    {
        return 5;
    }
    else if(c <= 115)
    {
        return 6;
    }
    else
    {
        return 7;
    }
}

/* TODO remove redundant logic in these */
void moveTextObject(Object * obj, int x, int y)
{
    SDL_Rect clip;
    int i = 0;

    while(obj != NULL)
    {
        clip = obj->clip;

        obj->x += (x + ((obj->clip.w * 0.5 * obj->scale) * i++));
        obj->y += y;
        clip.x += clip.w * obj->subImage;
        applyTexture(obj->x, obj->y, obj->image, &clip, obj->scale);
        obj = obj->next;
    }
}

void positionTextObject(Object * obj, int x, int y)
{
    SDL_Rect clip;
    int i = 0;

    while(obj != NULL)
    {
        clip = obj->clip;

        obj->x = (x + ((obj->clip.w * 0.5 * obj->scale) * i++));
        obj->y = y;
        clip.x += clip.w * obj->subImage;
        applyTexture(obj->x, obj->y, obj->image, &clip, obj->scale);
        obj = obj->next;
    }
}

void positionObject(Object * obj, int x, int y)
{
    SDL_Rect clip = obj->clip;

    obj->x = x;
    obj->y = y;
    clip.x += clip.w * obj->subImage;
    applyTexture(obj->x, obj->y, obj->image, &clip, obj->scale);
}

void moveObject(Object * obj, int x, int y)
{
    SDL_Rect clip = obj->clip;

    obj->x += x;
    obj->y += y;
    clip.x += clip.w * obj->subImage;
    applyTexture(obj->x, obj->y, obj->image, &clip, obj->scale);
}

Object * createObject(SDL_Texture * image, int subImage, int subImageNumber, objectType type, uint16_t lives, int x, int y, int w, int h, float scale)
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
    obj->lives = lives;
    obj->scale = scale;

    obj->clip.x = x;
    obj->clip.y = y;
    obj->clip.w = w;
    obj->clip.h = h;

    obj->next = NULL;

    return obj;
}

int countObjects(Object * obj)
{
    int count = 0;

    while(obj != NULL)
    {
        count++;
        obj = obj->next;
    }

    return count;
}

void freeObjects(Object * obj)
{
    Object * temp = NULL;

    while(obj != NULL)
    {
        temp = obj;
        obj = obj->next;
        free(temp);
    }
}
