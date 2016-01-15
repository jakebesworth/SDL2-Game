# System Dependancies
SDL_DEVELOPMENT_INC := C:\MinGW\SDL2\include\SDL2
SDL_DEVELOPMENT_DIR := C:\MinGW\SDL2\lib

# Compiler Parts
CC := gcc
CFLAGS += -Wall -Werror -pedantic -Wshadow -Wstrict-aliasing -Wstrict-overflow
OPT := -O2

INCLUDE :=  -I$(SDL_DEVELOPMENT_INC) -Iinclude

# Files
SRC_DIR := src/
SRC := $(SRC_DIR)main.c

# Build Environment
ifeq ($(OS),Windows_NT)
    STD := -std=c11
    OBJ := star.exe
    LIBRARY := -L$(SDL_DEVELOPMENT_DIR) -Llib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S), Darwin)
        STD := 
        OBJ := star
        LIBRARY := -F$(SDL_DEVELOPMENT_DIR) -framework SDL2
    else ifeq ($(UNAME_S), Linux)
        STD := -std=c99
    endif
endif

all: $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(STD) $(OPT) $(INCLUDE) $(LIBRARY) -o $(OBJ)
