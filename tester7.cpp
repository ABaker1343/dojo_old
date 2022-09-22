#include "src/headers/dojo.hpp"
#include "src/headers/fileHandler.hpp"

#include <vector>

int main () {
    FileHandler::shaderPath = "src/shaders/";

    std::vector<float> *vertices = new std::vector<float>();
    std::vector<float> *textures = new std::vector<float>();
    std::vector<float> *normals = new std::vector<float>();

    FileHandler::loadModelFBX("runner.fbx", vertices, textures, normals);
}
