# g++ will compile with typesafe and other c++11 errors
CC := gcc
SRC := c.c

CFLAGS += -Wall -pedantic -Werror

SDL_DEVELOPMENT_DIR := C:\MinGW\SDL2\include\SDL2
INCLUDE :=  -I$(SDL_DEVELOPMENT_DIR) -Iinclude

# Operating system dependant variables
ifeq ($(OS),Windows_NT)
    STD := -std=c11
    OBJ := c.exe
    LIBRARY := -LC:\MinGW\SDL2\lib -Llib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        STD := -std=c99
    endif
endif


all: windows

windows: c.c
	$(CC) $(SRC) $(CFLAGS) $(STD) $(INCLUDE) $(LIBRARY) -o $(OBJ)

mac: c.c
