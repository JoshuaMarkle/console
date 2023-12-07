#pragma once
#include <SDL.h>

class Window {
public:
	Window() {
		SDL_Init(SDL_INIT_VIDEO);

		const int WINDOW_WIDTH = 600;
		const int WINDOW_HEIGHT = 400;

		SDLWindow = SDL_CreateWindow(
		  "Hello Window",
		  SDL_WINDOWPOS_UNDEFINED,
		  SDL_WINDOWPOS_UNDEFINED,
		  WINDOW_WIDTH, WINDOW_HEIGHT, 0
		);

		SDLWindowSurface = SDL_GetWindowSurface(SDLWindow);
		Update();
	}

	void Update() {
		SDL_FillRect(
		  SDLWindowSurface,
		  nullptr,
		  SDL_MapRGB(SDLWindowSurface->format, 0, 40, 40)
		);
	}

	void RenderFrame() {
		SDL_UpdateWindowSurface(SDLWindow);
	}

	SDL_Surface* GetSurface() {
		return SDLWindowSurface;
	}

	private:
		SDL_Window* SDLWindow { nullptr };
		SDL_Surface* SDLWindowSurface { nullptr };
};
