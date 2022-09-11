#ifndef __HEADER_WINDOW
#define __HEADER_WINDOW

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdexcept>

#include "camera2D.hpp"
#include "gameObject2DSprite.hpp"
#include "gameObject2DAnimatedSprite.hpp"
#include "gameObject2DCollisionBox.hpp"
#include "renderable.hpp"

#define KEYS_SIZE 349

namespace dojo {
    class Window {
        public:
            Window(int width, int height, const char* name);
            ~Window();

            static bool KEYS[KEYS_SIZE];

            void clear();
            bool isAlive();
            void setKill();
            void render2D(Camera2D *c, GameObject2DSprite *s);
            void render2D(Camera2D *c, GameObject2DAnimatedSprite *s);
            void render2D(Camera2D *c, GameObject2DCollisionBox *b);

        private:
            GLFWwindow* window;
            unsigned int collisionBox2DShaderProgram;
            unsigned int collisionBoxVertexArray;
            unsigned int collisionBoxVertexBuffer;
            unsigned int boxElementBuffer;
            std::vector<float> *boxVertices;
            std::vector<unsigned int> *boxElements;

            void createCollisionBoxRenderDependancies();
            static void windowResizeCallback(GLFWwindow* window, int width, int height);
            static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);


    };
};

#endif
