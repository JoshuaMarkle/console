#include "Renderer.h"

// Constructor
Renderer::Renderer(SDL_Renderer* renderer, Object& camera) : renderer(renderer), camera(camera) {}

// Destructor
Renderer::~Renderer() {
    // SDL_Renderer should be destroyed elsewhere, not here
}

// Clear the screen
void Renderer::ClearScreen() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);
}

// Draw a line between two points
void Renderer::DrawLine(const Vector3D& start, const Vector3D& end) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color for the line
    SDL_RenderDrawLine(renderer, static_cast<int>(start.x), static_cast<int>(start.y), static_cast<int>(end.x), static_cast<int>(end.y));
}

// Present the renderer
void Renderer::RenderPresent() {
    SDL_RenderPresent(renderer);
}

void Renderer::RenderObject(const Object& object) {
    // Create a projection matrix
    float fov = 100.0f;
    float aspectRatio = static_cast<float>(Settings::NES_WIDTH) / Settings::NES_HEIGHT;
    Matrix4x4 projMatrix = CreateProjectionMatrix(fov, aspectRatio, 0.1f, 1000.0f);

    // Transform and project object vertices
    auto transformedVertices = object.GetVertices();
    std::vector<Vector3D> projectedVertices;
    for (const auto& vertex : transformedVertices) {
        Vector3D offsetVertex = vertex - camera.position;  // Apply camera offset
        Vector3D transformed = Transform(offsetVertex, projMatrix);

        // Apply perspective division
        if (transformed.z != 0) {
            transformed.x /= transformed.z;
            transformed.y /= transformed.z;
        }

        int screenX = static_cast<int>((transformed.x + 1) * 0.5f * Settings::NES_WIDTH);
        int screenY = static_cast<int>((1 - transformed.y) * 0.5f * Settings::NES_HEIGHT);
        projectedVertices.push_back(Vector3D(screenX, screenY, 0));
    }

    // Render the object edges
    for (const auto& edge : object.GetEdges()) {
        const auto& startVertex = projectedVertices[edge.first];
        const auto& endVertex = projectedVertices[edge.second];
        DrawLine(startVertex, endVertex);
    }
}
