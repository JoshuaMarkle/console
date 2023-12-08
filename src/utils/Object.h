#ifndef OBJECT_H
#define OBJECT_H

#include "MathUtil.h"
#include <vector>
#include <utility>

class Object {
public:
    Object(std::vector<Vector3D> vertices, std::vector<std::pair<int, int>> edges);

    std::vector<Vector3D> GetTransformedVertices() const;
	const std::vector<std::pair<int, int>>& GetEdges() const;

    Vector3D position;
    Vector3D rotation;
    Vector3D scale;    // To be implemented later

private:
    std::vector<Vector3D> vertices;
	std::vector<std::pair<int, int>> edges;
};

#endif // OBJECT_H
