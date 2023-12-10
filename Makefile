#lib/SDL/include #/usr/include/SDL2
SDL_PATH = /usr/include/SDL2

# Compiler Settings
CC = g++

CFLAGS  = -I$(SDL_PATH)
CFLAGS += -lSDL2
# CFLAGS += -lSDL2_ttf
CFLAGS += ./src/core/Object.cpp
CFLAGS += ./src/renderer/Renderer.cpp
CFLAGS += ./src/utils/MathUtil.cpp
CFLAGS += ./src/utils/OBJLoader.cpp

SRC  = src/main.cpp
EXEC = bin/game

all: clean build check run

# Clean Away Old Executables
clean:
	rm -f $(EXEC)

# Build The Executable
build:
	@echo "Building..."
	# g++ -I/usr/include/SDL2 -lSDL2 -lSDL2_ttf ./src/main/main.cpp -o game
	-@$(CC) $(CFLAGS) $(SRC) -o $(EXEC) 2> build.log

# Check For Errors
check:
	@if [ -s build.log ]; then \
		echo "Build Warnings/Errors Detected:" \
		echo | bat build.log; \
		exit 1; \
	else \
		echo "Build Successful"; \
	fi

# Run The Game
run:
	@sudo ./$(EXEC)

.PHONY: clean build check run
