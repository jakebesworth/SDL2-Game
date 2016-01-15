SDL_DEVELOPMENT_INC := C:\MinGW\SDL2\include\SDL2
SDL_DEVELOPMENT_LIB := C:\MinGW\SDL2\lib

# g++ will compile with typesafe and other c++11 errors
CC := gcc
SRC := c.c
OPT := -O2

CFLAGS += -Wall -Werror -pedantic -Wshadow -Wstrict-aliasing -Wstrict-overflow

INCLUDE :=  -I$(SDL_DEVELOPMENT_INC) -Iinclude

# Operating system dependant variables
ifeq ($(OS),Windows_NT)
    STD := -std=c11
    OBJ := c.exe
    LIBRARY := -L$(SDL_DEVELOPMENT_LIB) -Llib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        STD := -std=c99
    endif
endif


all: windows

windows: c.c
	$(CC) $(SRC) $(CFLAGS) $(STD) $(OPT) $(INCLUDE) $(LIBRARY) -o $(OBJ)

mac: c.c
