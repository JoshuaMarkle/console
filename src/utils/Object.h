#ifndef OBJECT_H
#define OBJECT_H

#include "MathUtil.h"
#include <vector>
#include <utility>

class Vector2D {
public:
	float u, v;
	Vector2D(float u = 0, float v = 0): u(u), v(v) {}
};

class Object {
public:
    Object(
		std::vector<Vector3D> vertices,
		std::vector<Vector2D> uvs,
		std::vector<std::pair<int, int>> edges);
	Object();

    std::vector<Vector3D> GetVertices() const;
	const std::vector<std::pair<int, int>>& GetEdges() const;

    Vector3D position;
    Vector3D rotation;
    Vector3D scale;

private:
    std::vector<Vector3D> vertices;
	std::vector<Vector2D> uvs;
	std::vector<std::pair<int, int>> edges;
};

#endif // OBJECT_H
