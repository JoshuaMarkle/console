#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include "MathUtil.h"

class Renderer {
public:
    Renderer(SDL_Renderer* sdlRenderer);
    ~Renderer();

    void ClearScreen();
    void DrawLine(const Vector3D& start, const Vector3D& end);
    void RenderPresent();

private:
    SDL_Renderer* sdlRenderer;
};

#endif // RENDERER_H
