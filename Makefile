# Compiler Settings
CC=g++
CFLAGS=-Iinclude/SDL/include -Linclude/SDL/lib -lSDL2 -lSDL2_ttf
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
	# g++ -I/usr/include/SDL2 -lSDL2 -lSDL2_ttf ./src/main/main.cpp -o game
	-@$(CC) $(CFLAGS) $(SRC) -o $(EXEC) 2> build.log

# Check For Errors
check:
	@echo "Checking For Errors..."
	@if [ -s build.log ]; then \
		echo "Build Warnings/Errors Detected:" \
		echo | cat build.log; \
		exit 1; \
	else \
		echo "Build Successful"; \
	fi

# Run The Game
run:
	@echo "Running Game..."
	@echo "Sudo Privliges Required!"
	@sudo ./$(EXEC)

.PHONY: clean build check run
