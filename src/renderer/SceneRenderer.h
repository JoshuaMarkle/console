#ifndef SCENERENDERER_H
#define SCENERENDERER_H

#include "Renderer.h"
#include "../utils/Object.h"
#include "../utils/MathUtil.h"

class SceneRenderer {
public:
    SceneRenderer(Renderer& renderer, Object& camera);

    void RenderObject(const Object& object);

private:
    Renderer& renderer;
	Object& camera;
};

#endif // SCENERENDERER_H
