# Compiler Settings
CC=g++
CFLAGS=-I/usr/include/SDL2 -lSDL2 -lSDL2_ttf
SRC=./src/main/main.cpp
EXEC=game

all: clean build check run

# Clean Away Old Executables
clean:
	@echo "Cleaning..."
	rm -f $(EXEC)

# Build The Executable
build:
	@echo "Building..."
	@$(CC) $(CFLAGS) $(SRC) -o $(EXEC) 2> build.log

# Check For Errors
check:
	@echo "Checking For Errors..."
	@if [ -s build.log ]; then \
		echo "Build Warnings/Errors Detected:" \
		cat build.log; \
	else \
		echo "Build Successful"; \
	fi

# Run The Game
run:
	@echo "Running Game..."
	@echo "Sudo Privliges Required!"
	@sudo ./$(EXEC)

.PHONY: clean build check run
