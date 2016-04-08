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

int objectCollision(Object * obj1, Object * obj2)
{
    if(((obj1->x + obj1->clip.w) >= obj2->x) && ((obj1->y + obj1->clip.h) >= obj2->y) && ((obj2->x + obj2->clip.w) >= obj1->x) && ((obj2->y + obj2->clip.h) >= obj1->y))
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

Object * createTextObject(SDL_Texture * image, char * text, objectType type)
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

    for(i = 0; i < textLength; i++)
    {
        if(i == 0)
        {
            obj = createObject(image, 0, 1, type, 1, (getTextX(text[i]) * width), (getTextY(text[i]) * height), width, height);
            objRoot = obj;
        }
        else
        {
            obj->next = createObject(image, 0, 1, type, 1, (getTextX(text[i]) * width), (getTextY(text[i]) * height), width, height);
            obj = obj->next;
        }
    }

    return objRoot;
}

int getTextX(char c)
{
    /* If capital letters, set to lowercase */
    if(c >= 65 && c <= 90)
    {
        c += 0x20;
    }

    /* Both getText functions work off of ASCII values mapping to spots on a 12x3 font-sheet */
    if(c <= 57)
    {
        return (c - 46);
    }
    else if(c <= 108)
    {
        return (c - 97);
    } 
    else if(c <= 120)
    {
        return (c - 109);
    }
    else
    {
        return (c - 121);
    }
}

int getTextY(char c)
{
    if(c >= 65 && c <= 90)
    {
        c += 0x20;
    }

    if(c <= 57 || c >= 121)
    {
        return 2;
    }
    else if(c >= 109)
    {
        return 1;
    }
    else
    {
        return 0;
    } 
}

void moveTextObject(Object * obj, int x, int y)
{
    SDL_Rect clip;
    int i = 0;

    while(obj != NULL)
    {
        clip = obj->clip;

        obj->x += (x + ((obj->clip.w * 0.75) * i++));
        obj->y += y;
        clip.x += clip.w * obj->subImage;
        applyTexture(obj->x, obj->y, obj->image, &clip);
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

        obj->x = (x + ((obj->clip.w * 0.75) * i++));
        obj->y = y;
        clip.x += clip.w * obj->subImage;
        applyTexture(obj->x, obj->y, obj->image, &clip);
        obj = obj->next;
    }
}

void positionObject(Object * obj, int x, int y)
{
    SDL_Rect clip = obj->clip;

    obj->x = x;
    obj->y = y;
    clip.x += clip.w * obj->subImage;
    applyTexture(obj->x, obj->y, obj->image, &clip);
}

void moveObject(Object * obj, int x, int y)
{
    SDL_Rect clip = obj->clip;

    obj->x += x;
    obj->y += y;
    clip.x += clip.w * obj->subImage;
    applyTexture(obj->x, obj->y, obj->image, &clip);
}

Object * createObject(SDL_Texture * image, int subImage, int subImageNumber, objectType type, uint16_t lives, int x, int y, int w, int h)
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
