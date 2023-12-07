#include <SDL.h>
#include "Renderer.h"
#include "MathUtil.h"
#include "SceneRenderer.h"
#include "OBJLoader.h"
#include <vector>

int main(int argc, char* args[]) {
    // Initialize SDL and create a window and renderer
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("3D Cube Projection", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Renderer renderer(sdlRenderer);
	SceneRenderer sceneRenderer(renderer);

	// Create cube
	Object cube = OBJLoader::Load("assets/models/cube.obj");
	cube.position = Vector3D(0, 0, 6); 

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
        renderer.ClearScreen();

		// Render cube
		cube.position.x = sin(counter);
		cube.position.y = cos(counter);
		sceneRenderer.RenderObject(cube);

        // Update the screen
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
