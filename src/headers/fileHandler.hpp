#ifndef __HEADER_FILE_HANDLER
#define __HEADER_FILE_HANDLER

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

class FileHandler  {
public:
    struct FBX_ARRAY_TYPE {
        unsigned int arrayLength;
        unsigned int encoding;
        unsigned int compressedLength;
        void* data;
    };

    struct FBX_SPECIAL_TYPE {
        unsigned int length;
        char* data;
    };

    struct FBX_PROPERTY {
        char typeCode;
        void* data;
    };

    struct FBX_NODE {
        unsigned int endOffset;
        unsigned int numProperties;
        unsigned int propertyListLen;
        unsigned char nameLen;
        char* name;
        FBX_PROPERTY* properties;
        unsigned int numSubNodes;
        FBX_NODE* nestedNodes;
        FBX_NODE* parentNode;
    };

    static std::string shaderPath;

    static std::string readShader(std::string filepath);
    static void loadModel(const char* filepath, std::vector<float> *vertices,
            std::vector<float> *textureCoords, std::vector<float> *normals, std::vector<unsigned int> *elements);
    static unsigned char* loadImage(const char* filepath, int &width, int& height, int& numChannels);
    static void loadModelFBX(const char* filepath, std::vector<float> *vertices, std::vector<float> *textures, std::vector<float> *normals);

private:
    static void readNode(FBX_NODE *rootNode, std::vector<char> *buffer, unsigned long &filemark);
    static void freeNodes(FBX_NODE *node);


};

#endif
