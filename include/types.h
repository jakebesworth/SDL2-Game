typedef enum
{
    SHIP,
    ASTEROID_SMALL,
    ASTEROID_MEDIUM,
    ASTEROID_LARGE,
    WALL,
    OBJECT_TYPE_SIZE
} objectType;

typedef struct object
{
    objectType type;
    SDL_Surface * image;
    SDL_Rect clip;
    uint16_t subImage;
    uint16_t subImageNumber;
    int x;
    int y;
    struct object * next;
} Object;

