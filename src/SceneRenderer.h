#ifndef SCENERENDERER_H
#define SCENERENDERER_H

#include "Renderer.h"
#include "Object.h"

class SceneRenderer {
public:
    SceneRenderer(Renderer& renderer);

    void RenderObject(const Object& object);

private:
    Renderer& renderer;
};

#endif // SCENERENDERER_H
