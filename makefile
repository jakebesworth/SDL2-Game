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
SRC := $(SRC_DIR)main.c

# Include Files

# Build Environment
ifeq ($(OS),Windows_NT)
    STD := -std=c11
    OBJ := star_win.exe
    LIBRARY := -L$(SDL_DEVELOPMENT_DIR) -Llib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S), Darwin)
        STD := 
        OBJ := star_osx
        LIBRARY := -F$(SDL_DEVELOPMENT_DIR) -framework SDL2
    else ifeq ($(UNAME_S), Linux)
        STD := -std=c99
        OBJ := star_linux
        LIBRARY := $(shell sdl2-config --libs)
        CFLAGS += $(shell sdl2-config --cflags)
    endif
endif

all: $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(STD) $(OPT) $(INCLUDE) $(LIBRARY) -o $(OBJ)
