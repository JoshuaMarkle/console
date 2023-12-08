#include <SDL.h>
#include "utils/Settings.h"
#include "renderer/Renderer.h"
#include "renderer/SceneRenderer.h"
#include "utils/MathUtil.h"
#include "utils/OBJLoader.h"
#include <vector>

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

    Renderer renderer(sdlRenderer);
	SceneRenderer sceneRenderer(renderer);

	// Create cube
	Object cube = OBJLoader::Load("assets/models/cube.obj");
	cube.position = Vector3D(0, 0, 10); 

	Uint32 lastTime = SDL_GetTicks(), currentTime;
	float counter;
    float deltaTime;

    // Main loop
    bool quit = false;
    SDL_Event e;
    while (!quit) {
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - lastTime) / 1000.0f;
		lastTime = currentTime;
		counter += deltaTime;

        // Handle events
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            // Handle other events like keyboard, mouse, etc.
        }

        // Clear the renderer
		SDL_SetRenderTarget(sdlRenderer, nesTexture);
        renderer.ClearScreen();

		// Render cube
		cube.position.x = sin(counter);
		cube.position.y = cos(counter);
		sceneRenderer.RenderObject(cube);

        // Update the screen
		SDL_SetRenderTarget(sdlRenderer, NULL);
		SDL_RenderCopy(sdlRenderer, nesTexture, NULL, NULL);
        renderer.RenderPresent();

        // Delay for visibility
        SDL_Delay(16); // ~60 frames per second
    }

    // Clean up SDL
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
