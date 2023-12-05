#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_keycode.h>
#include <iostream>
#include <string>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

SDL_Texture* renderText(const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize, SDL_Renderer *renderer) {
	// Open the font
	TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
	if (font == nullptr) {
		std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
		return nullptr;
	}

	// Render the message to a surface
	SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
	if (surf == nullptr) {
		TTF_CloseFont(font);
		std::cerr << "TTF_RenderText Error: " << TTF_GetError() << std::endl;
		return nullptr;
	}

	// Convert the surface to a texture
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	
	if (texture == nullptr) {
		std::cerr << "CreateTexture Error: " << SDL_GetError() << std::endl;
	}

	return texture;
}

int main(int argc, char* argv[]) {
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	// Initialize TTF
	if (TTF_Init() != 0) {
		std::cerr << "TTF_Init_Error: " << TTF_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	// Create Window
	SDL_Window *window = SDL_CreateWindow("Hello World!", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	// Create Renderer
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	// Load text texture
	SDL_Color textColor = {255, 255, 255, 255};
	SDL_Texture *textTexture = renderText("my favorite text", "assets/fonts/arcade.ttf", textColor, 12, renderer);

	// Event loop
	Uint32 startTime = SDL_GetTicks();
	SDL_Event event;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			} else if (event.type == SDL_KEYDOWN) {
				// Exit on the Esc key
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					quit = true;
				}
			}
		}

		// Quit after 5 seconds (5000 milliseconds)
		if (SDL_GetTicks() - startTime > 5000) {
			quit = true;
		}

		// Clear screen
		SDL_RenderClear(renderer);

		// Render text
		int textWidth, textHeight;
		SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);
		SDL_Rect textRect = { (WINDOW_WIDTH - textWidth) / 2, (WINDOW_HEIGHT - textHeight) / 2, textWidth, textHeight };
		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

		// Update the screen
		SDL_RenderPresent(renderer);
	}

	// Clean up
	SDL_DestroyTexture(textTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();

	return 0;
}
