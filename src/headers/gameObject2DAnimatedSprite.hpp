#ifndef __HEADER_GAME_OBJECT_2D_ANIMATED_SPRITE
#define __HEADER_GAME_OBJECT_2D_ANIMATED_SPRITE

#include "gameObject.hpp"
#include "renderable.hpp"

#include <string>
#include <unordered_map>

namespace dojo {

class GameObject2DAnimatedSprite : public GameObject, public Renderable {
    public:
        GameObject2DAnimatedSprite(int numFrames, std::string animationPath,
                glm::vec3 pos = glm::vec3(0.f, 0.f, 0.f), glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f));
        GameObject2DAnimatedSprite(GameObject2DAnimatedSprite* obj,
                glm::vec3 pos = glm::vec3(0.f, 0.f, 0.f), glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f));
        ~GameObject2DAnimatedSprite();

        void addAnimation(std::string name, int numFrames, std::string animationPath);
        void setCurrentAnimation(std::string animationName);

        bool nextFrame();

        int currentFrame();
        float currentAnimationChunkSize();
        unsigned int currentTexture();
        std::string currentAnimationName();

        typedef struct ANIMATION_DATA {
            std::string name;
            int numFrames;
            int currentFrame;
            float chunkSize;
            unsigned int texture;
            unsigned int vertexBuffer;
        } ANIMATION;

    private:
        std::unordered_map<std::string, ANIMATION> *animations;
        ANIMATION *currentAnimation;

        bool isCopy;
};

}

#endif
