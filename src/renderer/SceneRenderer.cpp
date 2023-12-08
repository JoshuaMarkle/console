#include "SceneRenderer.h"
#include "../utils/Settings.h"
#include <iostream>

SceneRenderer::SceneRenderer(Renderer& renderer, Object& camera) : renderer(renderer), camera(camera) {}

void SceneRenderer::RenderObject(const Object& object) {
    // Create a projection matrix
    float fov = 100.0f;
    float aspectRatio = Settings::NES_WIDTH / Settings::NES_HEIGHT;
    Matrix4x4 projMatrix = CreateProjectionMatrix(fov, aspectRatio, 0.1f, 1000.0f);

    // Transform and project object vertices
    auto transformedVertices = object.GetVertices();
    std::vector<Vector3D> projectedVertices;
    for (const auto& vertex : transformedVertices) {
		// Offeset verties by the camera position
		Vector3D offsetVertex = Vector3D(
			vertex.x - camera.position.x,
			vertex.y - camera.position.y,
			vertex.z - camera.position.z);

        Vector3D transformed = Transform(offsetVertex, projMatrix); 

        // Apply perspective division
        if (transformed.z != 0) {
            transformed.x /= transformed.z;
            transformed.y /= transformed.z;
        }

        // Convert from 3D to 2D screen coordinates
        int screenX = static_cast<int>((transformed.x + 1) * 0.5f * Settings::NES_WIDTH); // Window width
        int screenY = static_cast<int>((1 - transformed.y) * 0.5f * Settings::NES_HEIGHT); // Window height
        projectedVertices.push_back(Vector3D(screenX, screenY, 0));
    }

    // Render the object edges
    for (const auto& edge : object.GetEdges()) {
        const auto& startVertex = projectedVertices[edge.first];
        const auto& endVertex = projectedVertices[edge.second];
        renderer.DrawLine(startVertex, endVertex);
    }
}
