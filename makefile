# System Dependancies
#   Windows
     SDL_DEVELOPMENT_INC := C:\MinGW\SDL2\include\SDL2
     SDL_DEVELOPMENT_DIR := C:\MinGW\SDL2\lib
#
#   Linux
#    SDL_DEVELOPMENT_INC := /usr/includes/SDL2
#
#   OS X
#    SDL_DEVELOPMENT_INC := 
#    SDL_DEVELOPMENT_DIR := 


# Compiler Parts
CC := gcc
CFLAGS += -Wall -Werror -pedantic -Wshadow -Wstrict-aliasing -Wstrict-overflow -g
OPT := -O2

INCLUDE :=  -I$(SDL_DEVELOPMENT_INC) -Iinclude

# Source Files
SRC_DIR := src/
MAIN := $(SRC_DIR)main.c
GLOBAL := $(SRC_DIR)global.c
WRAPPERS := $(SRC_DIR)wrappers.c
GAME := $(SRC_DIR)game.c

# Source Objects
OBJ_DIR := bin/
MAIN_OBJ := $(OBJ_DIR)main.o
GLOBAL_OBJ := $(OBJ_DIR)globals.o
WRAPPERS_OBJ := $(OBJ_DIR)wrappers.o
GAME_OBJ := $(OBJ_DIR)game.o

# Build Environment
ifeq ($(OS),Windows_NT)
    STD := -std=c11
    OBJ := star_win.exe
    LIBRARY := -L$(SDL_DEVELOPMENT_DIR) -Llib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2
    DOWNLOAD := `downloading SDL2 development library`
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S), Darwin)
        STD := 
        OBJ := star_osx
        LIBRARY := -F$(SDL_DEVELOPMENT_DIR) -framework SDL2
        DOWNLOAD := `downloading SDL2 framework library`
    else ifeq ($(UNAME_S), Linux)
        STD := -std=c99
        OBJ := star_linux
        LIBRARY := $(shell sdl2-config --libs)
        CFLAGS += $(shell sdl2-config --cflags)
        DOWNLOAD := `sudo apt-get install libsdl2-dev`
    endif
endif

all: SDL $(OBJ)

$(OBJ): $(GLOBAL_OBJ) $(WRAPPERS_OBJ) $(GAME_OBJ) $(MAIN_OBJ) 
	$(CC) $(MAIN_OBJ) $(GLOBAL_OBJ) $(WRAPPERS_OBJ) $(GAME_OBJ) -o $(OBJ) $(LIBRARY)

$(MAIN_OBJ): $(MAIN)
	$(CC) -c $(MAIN) $(CFLAGS) $(STD) $(OPT) $(INCLUDE) -o $(MAIN_OBJ) $(LIBRARY)

$(GLOBAL_OBJ): $(GLOBAL)
	$(CC) -c $(GLOBAL) $(CFLAGS) $(STD) $(OPT) $(INCLUDE) -o $(GLOBAL_OBJ)

$(WRAPPERS_OBJ): $(WRAPPERS)
	$(CC) -c $(WRAPPERS) $(CFLAGS) $(STD) $(OPT) $(INCLUDE) -o $(WRAPPERS_OBJ) $(LIBRARY)

$(GAME_OBJ): $(GAME)
	$(CC) -c $(GAME) $(CFLAGS) $(STD) $(OPT) $(INCLUDE) -o $(GAME_OBJ) $(LIBRARY)

SDL:
ifneq ($(wildcard $(SDL_DEVELOPMENT_INC/SDL.h)),)
	$(error SDL2 development package not found, try $(DOWNLOAD))
endif

clean:
	rm -f bin/*

valgrind: all
	valgrind --leak-check=full --track-origins=yes ./$(OBJ)

drmemory: all
	drmemory $(OBJ)
