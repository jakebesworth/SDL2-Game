#
#   Makefile
#
#   Description
#       Make tool build for SDL2-Game
#
#   Author
#       Jake Besworth
#

# System Dependancies

# Windows Dependant Variables
ifeq ($(OS),Windows_NT)
    # SDL Development include file and directory
    SDL_DEVELOPMENT_INC := C:\MinGW\SDL2\include
    SDL_DEVELOPMENT_DIR := C:\MinGW\SDL2\lib\x86

    # GNU Compiler Standard
    STD := -std=c11

    # Binary File
    OBJ := star.exe

    # Library Flags
    LIBRARY := -L$(SDL_DEVELOPMENT_DIR) -Llib -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2

    # Download Message
    DOWNLOAD := `downloading SDL2 development library`

    # Distribution
    DIST_NAME := SDL2-game-windows
    DIST_DEPENDENCIES := SDL2.dll
else
    #UNAME Shell Variable
    UNAME_S := $(shell uname -s)

    # OS X Dependant Variables
    ifeq ($(UNAME_S), Darwin)
        # SDL Development include file and directory
        SDL_DEVELOPMENT_INC := ./Library/Frameworks/SDL2.framework/Headers
        SDL_DEVELOPMENT_DIR := ./Library/Frameworks

        # GNU Compiler Standard - Clang does not have standard
        STD := -std=gnu11

        # Binary File
        OBJ := star

        # Library Flags
        LIBRARY := -Wl,-rpath,@executable_path/$(SDL_DEVELOPMENT_DIR) -F$(SDL_DEVELOPMENT_DIR) -framework SDL2

        # Download Message
        DOWNLOAD := `downloading SDL2 framework library`

        # Distribution
        DIST_NAME := SDL2-game-osx
        DIST_DEPENDENCIES := Library

    # GNU/Linux Depedant Variables
    else ifeq ($(UNAME_S), Linux)
        # SDL Development include file and directory
        SDL_DEVELOPMENT_INC := /usr/include/SDL2

        # GNU Compiler Standard - Clang does not have standard
        STD := -std=c11

        # Binary File
        OBJ := star

        # Library and C Compiler Flags
        LIBRARY := $(shell sdl2-config --libs)
        CFLAGS += $(shell sdl2-config --cflags)

        # Download Message
        DOWNLOAD := `sudo apt-get install libsdl2-dev`

        # Distribution
        DIST_NAME := SDL2-game-linux
        DIST_DEPENDENCIES := $(OBJ)
    endif
endif

# development (3), and production (0)
DEBUG := -g0

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

# Distribution related Directories
ASSETS_DIR := assets/
DIST_DIR := dist/
LOGS_DIR := logs/

# Compiler
CC := gcc

# C Compiler Flags
CFLAGS += -Wall -Werror -pedantic -Wshadow -Wstrict-aliasing -Wstrict-overflow $(DEBUG)

# Optimizations
OPT := -O2 -flto

# Include directories
INCLUDE :=  -I$(SDL_DEVELOPMENT_INC) -I$(HEADER_DIR)

# Dependency Flags
DFLAGS := -MMD -MF

.PHONY: all SDL

all: SDL $(OBJ)

$(OBJ): $(OBJECT_FILES)
	@echo compiling binary \'$(OBJ)\'
	$(CC) $(DEBUG) $(STD) $(OPT) $(OBJECT_FILES) -o $(OBJ) $(LIBRARY)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) -c $< $(CFLAGS) $(STD) $(OPT) $(INCLUDE) $(DFLAGS) $(patsubst $(OBJ_DIR)%.o,$(DEPEND_DIR)%.d,$@) -o $@

# SDL Library Check
SDL:
ifeq ($(wildcard $(SDL_DEVELOPMENT_INC)),)
	$(error SDL2 development package [$(SDL_DEVELOPMENT_INC)] not found, try $(DOWNLOAD))
endif

-include $(DEPEND_FILES)

# Compile the distribution for the given system
.PHONY: dist

dist: $(DIST_DIR) $(DIST_DEPENDENCIES) $(ASSETS_DIR)
	@echo Compiling distribution build in \"$(DIST_DIR)\" as \"$(DIST_NAME).tar.gz\"
	mkdir $(DIST_DIR)$(DIST_NAME)
	mkdir $(DIST_DIR)$(DIST_NAME)/$(LOGS_DIR)
	cp $(OBJ) $(DIST_DIR)$(DIST_NAME)
	cp -r $(ASSETS_DIR) $(DIST_DIR)$(DIST_NAME)/
	cp -r $(DIST_DEPENDENCIES) $(DIST_DIR)$(DIST_NAME)/
	cp README* $(DIST_DIR)$(DIST_NAME)
	tar -zcvf $(DIST_DIR)$(DIST_NAME).tar.gz -C $(DIST_DIR) --remove-files $(DIST_NAME)

.PHONY: valgrind drmemory clean

clean:
	rm -f $(OBJ_DIR)*
	rm -f $(DEPEND_DIR)*
	rm -f $(OBJ)

valgrind: all
	valgrind --leak-check=yes --show-leak-kinds=all --track-origins=yes ./$(OBJ)

drmemory: all
	drmemory $(OBJ)
