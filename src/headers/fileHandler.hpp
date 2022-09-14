#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

namespace fileHandler {
    std::string readShader(std::string filepath);
    void loadModel(const char* filepath, std::vector<float> *vertices, std::vector<float> *textureCoords, std::vector<float> *normals, std::vector<unsigned int> *elements);
    unsigned char* loadImage(const char* filepath, int &width, int& height, int& numChannels);
}
