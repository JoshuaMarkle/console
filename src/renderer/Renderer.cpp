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

	// Create a Vector3D with the mainLight direction
	Vector3D mainLight = Vector3D(1, 1, 0);
	mainLight.Normalize();

	for (size_t i = 0; i < object.GetEdges().size(); i += 3) {
        const auto& vertexA = projectedVertices[object.GetEdges()[i].first];
        const auto& vertexB = projectedVertices[object.GetEdges()[i + 1].first];
        const auto& vertexC = projectedVertices[object.GetEdges()[i + 2].first];

        // Calculate normal of the triangle
        Vector3D edge1 = vertexB - vertexA;
        Vector3D edge2 = vertexC - vertexA;
        Vector3D normal = edge1.Cross(edge2);

        // Check if the triangle is facing the camera
        Vector3D viewVector = vertexA - camera.position;
        if (normal.Dot(viewVector) < 0) {
        }

		// Lighting
		float intensity = std::max(normal.Dot(mainLight), 0.0f);
		int c = static_cast<int>(255 * intensity);
		FillTriangle(vertexA, vertexB, vertexC, Color(c, c, c));
    }
}


void Renderer::FillTriangle(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3, const Color& color) {
    // Function to check if a point is inside the triangle
    auto isInsideTriangle = [](int x, int y, const Vector3D& v1, const Vector3D& v2, const Vector3D& v3) -> bool {
        float d1, d2, d3;
        bool has_neg, has_pos;

        d1 = (x - v2.x) * (v1.y - v2.y) - (v1.x - v2.x) * (y - v2.y);
        d2 = (x - v3.x) * (v2.y - v3.y) - (v2.x - v3.x) * (y - v3.y);
        d3 = (x - v1.x) * (v3.y - v1.y) - (v3.x - v1.x) * (y - v1.y);

        has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
        has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

        return !(has_neg && has_pos);
    };

    // Calculate bounding box of the triangle
    int minX = std::min({v1.x, v2.x, v3.x});
    int maxX = std::max({v1.x, v2.x, v3.x});
    int minY = std::min({v1.y, v2.y, v3.y});
    int maxY = std::max({v1.y, v2.y, v3.y});
	
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255); // Set color to white

    for (int y = minY; y <= maxY; y++) {
        for (int x = minX; x <= maxX; x++) {
            if (isInsideTriangle(x, y, v1, v2, v3)) {
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}
