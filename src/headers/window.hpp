#ifndef __HEADER_WINDOW
#define __HEADER_WINDOW

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/quaternion_transform.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <stdexcept>
#include <map>

#include "renderable.hpp"

#include "../gameObjects/headers/camera3D.hpp"
#include "../gameObjects/headers/gameObject2DSprite.hpp"
#include "../gameObjects/headers/gameObject2DAnimatedSprite.hpp"
#include "../gameObjects/headers/gameObject2DCollisionBox.hpp"
#include "../gameObjects/headers/gameObject3DTextured.hpp"
#include "../gameObjects/headers/gameObjectSpotLightSource.hpp"
#include "../gameObjects/headers/gameObjectPointLightSource.hpp"

#include "../menuItems/headers/menuItem.hpp"

#define KEYS_SIZE 349
#define MOUSE_BUTTONS_SIZE 8

namespace dojo {
    class Window {
        public:

            struct Character {
                unsigned int texture;
                glm::ivec2 size;
                glm::ivec2 bearing;
                //unsigned int advance;
                long advance;
            };

            Window(int width, int height, const char* name);
            ~Window();

            GLFWwindow* window;

            static int winWidth;
            static int winHeight;

            static bool KEYS[KEYS_SIZE];
            static bool MOUSE_BUTTONS[MOUSE_BUTTONS_SIZE];
            static double MOUSE_POSITION_X;
            static double MOUSE_POSITION_Y;

            bool isAlive();
            void setKill();
            void showPointer();
            void hidePointer();

        private:
            
            static void windowResizeCallback(GLFWwindow* window, int width, int height);
            static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
            static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
            static void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos);


    };
};

#endif
