#ifndef __HEADER_RENDERER
#define __HEADER_RENDERER

#include "window.hpp"

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <map>

#include "../gameObjects/headers/camera3D.hpp"
#include "../gameObjects/headers/gameObject2DSprite.hpp"
#include "../gameObjects/headers/gameObject2DAnimatedSprite.hpp"
#include "../gameObjects/headers/gameObject2DCollisionBox.hpp"
#include "../gameObjects/headers/gameObject3DTextured.hpp"
#include "../gameObjects/headers/gameObjectSpotLightSource.hpp"
#include "../gameObjects/headers/gameObjectPointLightSource.hpp"

#include "../menuItems/headers/menuItem.hpp"

namespace dojo {

class Renderer {
    public:

        struct Character {
            unsigned int texture;
            glm::ivec2 size;
            glm::ivec2 bearing;
            //unsigned int advance;
            long advance;
        };

        Renderer(Window *window);
        ~Renderer();

        void clear(Window *window);
        void clearShadow();

        void render(Window *window, Camera3D *c, GameObject2DSprite *s);
        void render(Window *window, Camera3D *c, GameObject2DAnimatedSprite *s);
        void render(Window *window, Camera3D *c, GameObject2DCollisionBox *b);
        void render(Window *window, Camera3D *c, GameObject3DTextured *cube, GameObjectSpotLightSource *light, float ambientIntensity = 0.15);
        void render(Window *window, Camera3D *c, GameObject3DTextured *cube, GameObjectPointLightSource *light, float ambientIntensity = 0.15);
        void render(Window *window, Camera3D *c, GameObjectSpotLightSource *light);
        void render(Window *window, Camera3D *c, GameObjectPointLightSource *light);

        void render(Window *window, MenuItem *item);

        void renderShadows(GameObject3DTextured *obj, GameObjectSpotLightSource *light);
        void renderShadows(GameObject3DTextured *obj, GameObjectPointLightSource *light);

        unsigned int renderTextToTexture(std::string text, unsigned int sizex, unsigned int sizey);

    private:
        unsigned int boxElementBuffer;

        std::vector<float> *boxVertices;
        std::vector<unsigned int> *boxElements;
        std::vector<float> *textVertices;
        glm::vec3 textColor;

        glm::vec4 colliderColor;

        std::map<char, Character> *characters;

        const unsigned int SHADOW_HEIGHT = 1024, SHADOW_WIDTH = 1024;

        // framebuffers
        unsigned int depthMapFrameBuffer = 0;
        unsigned int depthMap = 0;

        unsigned int depthCubeMapFrameBuffer = 0;
        unsigned int depthCubeMap = 0;

        unsigned int textFramebuffer = 0;

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
        unsigned int menuItemTexturedShaderProgram = 0;

        // methods

        void createShadowMapDependancies();
        void createShadowCubeMapDependancies();
        void createTextFramebuffer();

        void createCollisionBoxRenderDependancies();

        void createShaderPrograms();
};

}

#endif
