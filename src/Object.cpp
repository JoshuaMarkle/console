#include "Object.h"

Object::Object(std::vector<Vector3D> vertices, std::vector<std::pair<int, int>> edges)
	: vertices(vertices), edges(edges), position(0, 0, 0), rotation(0, 0, 0), scale(1, 1, 1) {}

std::vector<Vector3D> Object::GetTransformedVertices() const {
    std::vector<Vector3D> transformedVertices;
    Matrix4x4 transformMatrix;
    // Apply transformations based on position, rotation, scale
    // Currently only position is implemented
    transformMatrix.Translate(position);

    for (const auto& vertex : vertices) {
        transformedVertices.push_back(Transform(vertex, transformMatrix));
    }

    return transformedVertices;
}

const std::vector<std::pair<int, int>>& Object::GetEdges() const {
	return edges;
}
