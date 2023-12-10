#include "Object.h"

Object::Object(std::vector<Vector3D> vertices, std::vector<Vector2D> uvs, std::vector<std::pair<int, int>> edges)
	: vertices(vertices), uvs(uvs), edges(edges), position(0, 0, 0), rotation(0, 0, 0), scale(1, 1, 1) {}

Object::Object()
    : position(0, 0, 0), rotation(0, 0, 0), scale(1, 1, 1) {}

std::vector<Vector3D> Object::GetVertices() const {
    std::vector<Vector3D> transformedVertices;
    Matrix4x4 transformMatrix;

    // Apply rotation and position transformations
    transformMatrix.RotateX(rotation.x);
    transformMatrix.RotateY(rotation.y);
    transformMatrix.RotateZ(rotation.z);
    transformMatrix.Translate(position);

    for (const auto& vertex : vertices) {
        transformedVertices.push_back(Transform(vertex, transformMatrix));
    }

    return transformedVertices;
}

const std::vector<std::pair<int, int>>& Object::GetEdges() const {
	return edges;
}

// Add any additional methods needed for UV coordinate handling
