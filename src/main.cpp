#include <SDL.h>
#include "core/Settings.h"
#include "renderer/Renderer.h"
#include "utils/MathUtil.h"
#include "utils/OBJLoader.h"
#include <vector>
#include <iostream>

int main(int argc, char* args[]) {
    // Initialize SDL and create a window and renderer
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow(
		"AllPlay Console", 
		SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, 
		Settings::WINDOW_WIDTH, 
		Settings::WINDOW_HEIGHT, 
		SDL_WINDOW_SHOWN);
    SDL_Renderer* sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Create a texture for upscaled resolution
    SDL_Texture* nesTexture = SDL_CreateTexture(
		sdlRenderer, 
		SDL_PIXELFORMAT_ARGB8888, 
		SDL_TEXTUREACCESS_TARGET, 
		Settings::NES_WIDTH, 
		Settings::NES_HEIGHT);

	// Create camera
	Object camera = Object();
	float cameraSpeed = 200.0f;

	// Create cube
	Object cube = OBJLoader::Load("assets/models/centered_cow.obj");
	cube.position.z = 10; 

	// Create Renderers
    Renderer renderer(sdlRenderer, camera);

	Uint32 lastTime = SDL_GetTicks(), currentTime;
    float deltaTime;
	float counter;

    // Main loop
    bool quit = false;
    SDL_Event event;
    while (!quit) {
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - lastTime) / 1000.0f;
		lastTime = currentTime;
		counter += deltaTime;

		// Handle events
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			} else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_w: // Move up
						camera.position.y += cameraSpeed * deltaTime;
						break;
					case SDLK_s: // Move down
						camera.position.y -= cameraSpeed * deltaTime;
						break;
					case SDLK_a: // Move left
						camera.position.x -= cameraSpeed * deltaTime;
						break;
					case SDLK_d: // Move right
						camera.position.x += cameraSpeed * deltaTime;
						break;
					case SDLK_q: // Move forwards
						camera.position.z -= cameraSpeed * deltaTime;
						break;
					case SDLK_e: // Move backwards
						camera.position.z += cameraSpeed * deltaTime;
						break;
				}
			}
			// Handle other events...
		}

        // Clear the renderer
		SDL_SetRenderTarget(sdlRenderer, nesTexture);
        renderer.ClearScreen();

		// Make the cube spin!
		// cube.rotation.x = counter * 100.0f;
		// cube.rotation.y = counter * 120.0f;
		// cube.rotation.z = counter * 140.0f;
		renderer.RenderObject(cube);

        // Update the screen
		SDL_SetRenderTarget(sdlRenderer, NULL);
		SDL_RenderCopy(sdlRenderer, nesTexture, NULL, NULL);
        renderer.RenderPresent();

        // Delay for visibility
        // SDL_Delay(16); // ~60 frames per second
    }

    // Clean up SDL
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
