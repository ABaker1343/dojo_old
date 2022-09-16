#ifndef __HEADER_WINDOW
#define __HEADER_WINDOW

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdexcept>

#include "camera2D.hpp"
#include "camera3D.hpp"
#include "gameObject2DSprite.hpp"
#include "gameObject2DAnimatedSprite.hpp"
#include "gameObject2DCollisionBox.hpp"
#include "renderable.hpp"
#include "gameObject3DTextured.hpp"
#include "gameObjectSpotLightSource.hpp"

#define KEYS_SIZE 349

namespace dojo {
    class Window {
        public:
            Window(int width, int height, const char* name);
            ~Window();

            static int winWidth;
            static int winHeight;

            static bool KEYS[KEYS_SIZE];

            void clear();
            void clearShadow();
            bool isAlive();
            void setKill();

            void render(Camera3D *c, GameObject2DSprite *s);
            void render(Camera3D *c, GameObject2DAnimatedSprite *s);
            void render(Camera3D *c, GameObject2DCollisionBox *b);
            void render(Camera3D *c, GameObject3DTextured *cube, GameObjectSpotLightSource *light);
            void render(Camera3D *c, GameObjectSpotLightSource *light);

            void renderShadows(GameObject3DTextured *obj, GameObjectSpotLightSource *light);

        private:
            GLFWwindow* window;
            unsigned int collisionBoxShaderProgram;
            unsigned int collisionBoxVertexArray;
            unsigned int collisionBoxVertexBuffer;
            unsigned int boxElementBuffer;
            std::vector<float> *boxVertices;
            std::vector<unsigned int> *boxElements;
            glm::vec4 colliderColor;

            const unsigned int SHADOW_HEIGHT = 1024, SHADOW_WIDTH = 1024;
            unsigned int depthMapFrameBuffer = 0;
            unsigned int depthMap = 0;
            unsigned int shadowMapShaderProgram = 0;

            void createCollisionBoxRenderDependancies();
            void createShadowMapDependancies();
            static void windowResizeCallback(GLFWwindow* window, int width, int height);
            static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);


    };
};

#endif
