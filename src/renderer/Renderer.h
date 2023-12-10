#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include "../core/Object.h"
#include "../core/Color.h"
#include "../core/Settings.h"
#include "../utils/MathUtil.h"
#include <algorithm>

class Renderer {
public:
    Renderer(SDL_Renderer* renderer, Object& object);
    ~Renderer();

    void ClearScreen();
    void DrawLine(const Vector3D& start, const Vector3D& end);
    void RenderPresent();
	void RenderObject(const Object& object);
	void FillTriangle(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3, const Color& color);

private:
    SDL_Renderer* renderer;
	Object& camera;
};

#endif // RENDERER_H
