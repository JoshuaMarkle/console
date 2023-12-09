#include "OBJLoader.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <string>

Object OBJLoader::Load(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<Vector3D> vertices;
    std::vector<std::pair<int, int>> edges;

    if (!file.is_open()) {
        std::cout << "Error: File not found (" << filename << ")" << std::endl;
        return Object(); // Return an empty object or handle the error as needed
    }

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            float x, y, z;
            iss >> x >> y >> z;
            vertices.push_back(Vector3D(x, y, z));
        } else if (prefix == "f") {
            std::string vertex;
            std::vector<int> faceVertices;

            while (iss >> vertex) {
                std::istringstream vertexStream(vertex);
                std::string vertexIndex;
                std::getline(vertexStream, vertexIndex, '/');
                int idx = std::stoi(vertexIndex);
                faceVertices.push_back(idx - 1); // OBJ indices are 1-based
            }

            // Assuming the faces are triangles or quads
            edges.push_back({faceVertices[0], faceVertices[1]});
            edges.push_back({faceVertices[1], faceVertices[2]});

            if (faceVertices.size() == 4) { // It's a quad
                edges.push_back({faceVertices[2], faceVertices[3]});
                edges.push_back({faceVertices[3], faceVertices[0]});
            } else if (faceVertices.size() == 3) { // It's a triangle
                edges.push_back({faceVertices[2], faceVertices[0]});
            }
        }
    }

    return Object(vertices, edges);
}
