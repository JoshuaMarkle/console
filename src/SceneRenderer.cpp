#include "SceneRenderer.h"
#include "MathUtil.h"

SceneRenderer::SceneRenderer(Renderer& renderer) : renderer(renderer) {}

void SceneRenderer::RenderObject(const Object& object) {
    // Create a projection matrix
    float fov = 120.0f;
    float aspectRatio = 800.0f / 600.0f;
    Matrix4x4 projMatrix = CreateProjectionMatrix(fov, aspectRatio, 0.1f, 1000.0f);

    // Transform and project object vertices
    auto transformedVertices = object.GetTransformedVertices();
    std::vector<Vector3D> projectedVertices;
    for (const auto& vertex : transformedVertices) {
        Vector3D transformed = Transform(vertex, projMatrix); 

        // Apply perspective division
        if (transformed.z != 0) {
            transformed.x /= transformed.z;
            transformed.y /= transformed.z;
        }

        // Convert from 3D to 2D screen coordinates
        int screenX = static_cast<int>((transformed.x + 1) * 0.5f * 800); // Window width
        int screenY = static_cast<int>((1 - transformed.y) * 0.5f * 600); // Window height
        projectedVertices.push_back(Vector3D(screenX, screenY, 0));
    }

    // Render the object edges
    for (const auto& edge : object.GetEdges()) {
        const auto& startVertex = projectedVertices[edge.first];
        const auto& endVertex = projectedVertices[edge.second];
        renderer.DrawLine(startVertex, endVertex);
    }
}
