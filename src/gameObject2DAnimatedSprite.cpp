#include "headers/gameObject2DAnimatedSprite.hpp"

namespace dojo {

GameObject2DAnimatedSprite::GameObject2DAnimatedSprite(int numFrames, std::string animationPath) : GameObject() {

    animations = new std::vector<ANIMATION>();
    ANIMATION baseAnimation;

    baseAnimation.currentFrame = 0;
    baseAnimation.numFrames = numFrames;
    baseAnimation.chunkSize = 1.0f/numFrames;

    vertices = new std::vector<float> {
        // x, y, z, texture x, texture y
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, baseAnimation.chunkSize, 1.0f,
        1.0f, 0.0f, 0.0f, baseAnimation.chunkSize, 0.0f,
    };

    elements = new std::vector<unsigned int> {
        0, 1, 2,
        2, 3, 0,
    };

    Renderable::create2DBuffers(vertexArrayObject, baseAnimation.vertexBuffer, elementBuffer,
            vertices, elements);
    shaderProgram = Renderable::createBasicShaderProgram("src/shaders/basicVert.vert", "src/shaders/basicFrag.frag");
    baseAnimation.texture = Renderable::loadTextureFromFile(animationPath.c_str());

    animations->push_back(baseAnimation);
    currentAnimation = &(*animations)[0];

}

GameObject2DAnimatedSprite::~GameObject2DAnimatedSprite() {
    delete vertices;
    delete elements;
    delete animations;
        
}

int GameObject2DAnimatedSprite::currentFrame() {
    return currentAnimation->currentFrame;
}

float GameObject2DAnimatedSprite::currentAnimationChunkSize() {
    return currentAnimation->chunkSize;
}

unsigned int GameObject2DAnimatedSprite::currentTexture() {
    return currentAnimation->texture;
}

bool GameObject2DAnimatedSprite::nextFrame() {
    // move the animation along one frame
    // return true if there is another frame and false if the animation has finished
    if (currentAnimation->currentFrame >= currentAnimation->numFrames-1) {
        currentAnimation->currentFrame = 0;
        return false;
    }
    currentAnimation->currentFrame++;
    return true;
}

}
