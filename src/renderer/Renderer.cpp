#include "Renderer.h"

// Constructor
Renderer::Renderer(SDL_Renderer* sdlRenderer) : sdlRenderer(sdlRenderer) {}

// Destructor
Renderer::~Renderer() {
    // SDL_Renderer should be destroyed elsewhere, not here
}

// Clear the screen
void Renderer::ClearScreen() {
    SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(sdlRenderer);
}

// Draw a line between two points
void Renderer::DrawLine(const Vector3D& start, const Vector3D& end) {
    SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255); // White color for the line
    SDL_RenderDrawLine(sdlRenderer, static_cast<int>(start.x), static_cast<int>(start.y), static_cast<int>(end.x), static_cast<int>(end.y));
}

// Present the renderer
void Renderer::RenderPresent() {
    SDL_RenderPresent(sdlRenderer);
}
