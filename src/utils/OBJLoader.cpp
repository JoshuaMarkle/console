#include "OBJLoader.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

Object OBJLoader::Load(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<Vector3D> vertices;
    std::vector<std::pair<int, int>> edges;

	// Check if the file exists
	std::ifstream infile;
	infile.open(filename);
	if (!infile) {
		std::cout << "Error: File not found (" << filename << ")" << std::endl;
	}

	// Parse the obj file
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            float x, y, z;
            iss >> x >> y >> z;
            vertices.push_back(Vector3D(x, y, z));
        } else if (prefix == "f") {
            int a, b, c, d;
            iss >> a >> b >> c;
            edges.push_back({a - 1, b - 1});
            edges.push_back({b - 1, c - 1});
            
            if (iss >> d) { // Check if it's a quad
                edges.push_back({c - 1, d - 1});
                edges.push_back({d - 1, a - 1});
            } else { // It's a triangle
                edges.push_back({c - 1, a - 1});
            }
        }
    }

    return Object(vertices, edges);
}
