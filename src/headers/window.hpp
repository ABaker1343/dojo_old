#ifndef __HEADER_WINDOW
#define __HEADER_WINDOW

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdexcept>

#include "camera2D.hpp"
#include "gameObject2DSprite.hpp"
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
            void render2D(Camera2D *c, GameObject2DSprite* s);

        private:
            GLFWwindow* window;

            static void windowResizeCallback(GLFWwindow* window, int width, int height);
            static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);


    };
};

#endif
