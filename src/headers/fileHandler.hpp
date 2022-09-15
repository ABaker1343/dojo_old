#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

class FileHandler  {
public:

    static std::string shaderPath;

    static std::string readShader(std::string filepath);
    static void loadModel(const char* filepath, std::vector<float> *vertices,
            std::vector<float> *textureCoords, std::vector<float> *normals, std::vector<unsigned int> *elements);
    static unsigned char* loadImage(const char* filepath, int &width, int& height, int& numChannels);

};
