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

            void clear();
            void clearShadow();

            void render(Camera3D *c, GameObject2DSprite *s);
            void render(Camera3D *c, GameObject2DAnimatedSprite *s);
            void render(Camera3D *c, GameObject2DCollisionBox *b);
            void render(Camera3D *c, GameObject3DTextured *cube, GameObjectSpotLightSource *light);
            void render(Camera3D *c, GameObject3DTextured *cube, GameObjectPointLightSource *light);
            void render(Camera3D *c, GameObjectSpotLightSource *light);
            void render(Camera3D *c, GameObjectPointLightSource *light);

            void render(MenuItem *item);

            void renderShadows(GameObject3DTextured *obj, GameObjectSpotLightSource *light);
            void renderShadows(GameObject3DTextured *obj, GameObjectPointLightSource *light);

        private:
            GLFWwindow* window;
            unsigned int boxElementBuffer;

            std::vector<float> *boxVertices;
            std::vector<unsigned int> *boxElements;
            std::vector<float> *textVertices;
            glm::vec3 textColor;

            glm::vec4 colliderColor;

            std::map<char, Character> *characters;

            const unsigned int SHADOW_HEIGHT = 1024, SHADOW_WIDTH = 1024;

            unsigned int depthMapFrameBuffer = 0;
            unsigned int depthMap = 0;

            unsigned int depthCubeMapFrameBuffer = 0;
            unsigned int depthCubeMap = 0;

            // vertex Array Objects
            unsigned int collisionBoxVertexArray;
            unsigned int textVertexArray;

            // vertexBuffers
            unsigned int collisionBoxVertexBuffer = 0;
            unsigned int textVertexBuffer = 0;

            // shader programs
            unsigned int shaderProgram2D = 0;
            unsigned int collisionBoxShaderProgram;
            unsigned int textShaderProgram = 0;

            unsigned int shadowMapShaderProgram = 0;
            unsigned int spotLightShaderProgram = 0;

            unsigned int cubeMapShaderProgram= 0;
            unsigned int pointLightShaderProgram = 0;

            unsigned int menuItemShaderProgram = 0;

            // methods
            
            void createShadowMapDependancies();
            void createShadowCubeMapDependancies();

            void createCollisionBoxRenderDependancies();

            void createShaderPrograms();

            static void windowResizeCallback(GLFWwindow* window, int width, int height);
            static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
            static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
            static void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos);


    };
};

#endif
