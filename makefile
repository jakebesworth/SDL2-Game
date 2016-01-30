#
#   Makefile software build
#

# System Dependancies
ifeq ($(OS),Windows_NT)
    SDL_DEVELOPMENT_INC := C:\MinGW\SDL2\include\SDL2
    SDL_DEVELOPMENT_DIR := C:\MinGW\SDL2\lib
    STD := -std=c11
    OBJ := star_win.exe
    LIBRARY := -L$(SDL_DEVELOPMENT_DIR) -Llib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2
    DOWNLOAD := `downloading SDL2 development library`
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S), Darwin)
        SDL_DEVELOPMENT_INC := ./Library/Frameworks/SDL2.framework/Headers
        SDL_DEVELOPMENT_DIR := ./Library/Frameworks
        STD := 
        OBJ := star_osx
        LIBRARY := -Wl,-rpath,$(SDL_DEVELOPMENT_DIR) -F$(SDL_DEVELOPMENT_DIR) -framework SDL2
        DOWNLOAD := `downloading SDL2 framework library`
    else ifeq ($(UNAME_S), Linux)
        SDL_DEVELOPMENT_INC := /usr/include/SDL2
        STD := -std=c99
        OBJ := star_linux
        LIBRARY := $(shell sdl2-config --libs)
        CFLAGS += $(shell sdl2-config --cflags)
        DOWNLOAD := `sudo apt-get install libsdl2-dev`
    endif
endif

DEBUG := -g3

# Source Files
SRC_DIR := src/
SOURCE_FILES := $(wildcard $(SRC_DIR)*.c)

# Source Objects
OBJ_DIR := bin/
OBJECT_FILES := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SOURCE_FILES))

# Header Files
HEADER_DIR := include/

# Depend Files
DEPEND_DIR := depend/
DEPEND_FILES := $(patsubst $(SRC_DIR)%.c,$(DEPEND_DIR)%.d,$(SOURCE_FILES))

# Compiler Parts
CC := gcc
CFLAGS += -Wall -Werror -pedantic -Wshadow -Wstrict-aliasing -Wstrict-overflow $(DEBUG)
OPT := -O2 -flto
INCLUDE :=  -I$(SDL_DEVELOPMENT_INC) -I$(HEADER_DIR)
DFLAGS := -MMD -MF

.PHONY: all SDL

all: SDL $(OBJ)

$(OBJ): $(OBJECT_FILES)
	$(CC) $(DEBUG) $(STD) $(OPT) $(OBJECT_FILES) -o $(OBJ) $(LIBRARY)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) -c $< $(CFLAGS) $(STD) $(OPT) $(INCLUDE) $(DFLAGS) $(patsubst $(OBJ_DIR)%.o,$(DEPEND_DIR)%.d,$@) -o $@

SDL:
ifeq ($(wildcard $(SDL_DEVELOPMENT_INC)),)
	$(error SDL2 development package [$(SDL_DEVELOPMENT_INC)] not found, try $(DOWNLOAD))
endif

-include $(DEPEND_FILES)

.PHONY: valgrind drmemory clean

clean:
	rm -f $(OBJ_DIR)*
	rm -f $(DEPEND_DIR)*
	rm -f $(OBJ)

valgrind: all
	valgrind --leak-check=full --track-origins=yes ./$(OBJ)

drmemory: all
	drmemory $(OBJ)
