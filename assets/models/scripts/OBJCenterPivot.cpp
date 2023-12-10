#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

struct Vector3D {
    float x, y, z;

    Vector3D() : x(0), y(0), z(0) {}
    Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}

    Vector3D operator+(const Vector3D& other) const {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }

    Vector3D operator-(const Vector3D& other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    Vector3D operator/(float divisor) const {
        return Vector3D(x / divisor, y / divisor, z / divisor);
    }
};

void CenterPivot(const std::string& filepath) {
}

int main() {
    std::string filepath;
    std::cout << "Enter the path to the OBJ file: ";
    std::cin >> filepath;

	// Open the file
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: File not found (" << filepath << ")" << std::endl;
        return;
    }

    std::string line;
    std::vector<Vector3D> vertices;
    Vector3D center(0, 0, 0);

    // Read vertices
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            float x, y, z;
            iss >> x >> y >> z;
            Vector3D vertex(x, y, z);
            vertices.push_back(vertex);
            center = center + vertex;
        }
    }

    // Calculate center of mass
    center = center / static_cast<float>(vertices.size());

    // Shift vertices so that center of mass is at origin
    for (auto& vertex : vertices) {
        vertex = vertex - center;
    }

    file.close();

    // Generate output file path
    fs::path inputPath(filepath);
    fs::path outputPath = inputPath.parent_path() / ("centered_" + inputPath.filename().string());

    // Write the modified vertices back to a new OBJ file
    std::ofstream outFile(outputPath);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to create output file (" << outputPath << ")" << std::endl;
        return;
    }

    for (const auto& vertex : vertices) {
        outFile << "v " << vertex.x << " " << vertex.y << " " << vertex.z << "\n";
    }

    outFile.close();
    std::cout << "Centered OBJ file created: " << outputPath << std::endl;

    std::cout << "Program finished. Exiting..." << std::endl;
    return 0;
}
