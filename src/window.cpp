#include "headers/window.hpp"
#include "freetype/freetype.h"
#include <GLFW/glfw3.h>

namespace dojo {

bool Window::KEYS[KEYS_SIZE];
bool Window::MOUSE_BUTTONS[MOUSE_BUTTONS_SIZE];
int Window::winHeight, Window::winWidth;
double Window::MOUSE_POSITION_X, Window::MOUSE_POSITION_Y;

Window::Window(int width, int height, const char* name) {

    // initalize glfw and the window

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    winHeight = height; winWidth = width;

    window = glfwCreateWindow(
            winHeight, winHeight, name,
            NULL, NULL
    );

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, windowResizeCallback);
    glfwSetKeyCallback(window, keyCallback);

    if (glfwRawMouseMotionSupported()) {
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, mouseMoveCallback);

    //initalize opengl

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("failed to load opengl functions");
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    // allow color blending

    glViewport(0, 0, width, height);
    
    // initialize true type
    
    FT_Library freetype;
    if (FT_Init_FreeType(&freetype) != 0) {
        throw std::runtime_error("failed to initialize freetype font rendering library");
    }

    FT_Face ftArial;
    if (FT_New_Face(freetype, "fonts/arial.ttf", 0, &ftArial) != 0) {
        throw std::runtime_error("failed to load arial font");
    }

    FT_Set_Pixel_Sizes(ftArial, 0, 48);

    // create the fonts
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    characters = new std::map<char, Character>();

    for (unsigned char c = 0; c < 128; c++){
        
        // load the characters glyph
        if (FT_Load_Char(ftArial, c, FT_LOAD_RENDER) != 0) {
            std::cout << "failed to load character " << c << " in font arial" << std::endl;
            throw std::runtime_error("failed to load character in font");
        }

        //generate the texture for the font
        
        unsigned int glyphTexture = 0;
        glGenTextures(1, &glyphTexture);
        glBindTexture(GL_TEXTURE_2D, glyphTexture);

        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED, // one byte
                ftArial->glyph->bitmap.width,
                ftArial->glyph->bitmap.rows,
                0,
                GL_RED, // one byte
                GL_UNSIGNED_BYTE,
                ftArial->glyph->bitmap.buffer
            );

        // set the texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // create the character

        Character character = {
            glyphTexture,
            glm::ivec2(ftArial->glyph->bitmap.width, ftArial->glyph->bitmap.rows),
            glm::ivec2(ftArial->glyph->bitmap_left, ftArial->glyph->bitmap_top),
            ftArial->glyph->advance.x
        };

        characters->insert(std::pair<char, Character>(c, character));
    }

    FT_Done_Face(ftArial);
    FT_Done_FreeType(freetype);

    // initialize the window class and all its parts

    createShadowMapDependancies();
    createShadowCubeMapDependancies();

    createCollisionBoxRenderDependancies();
    colliderColor = glm::vec4(0.f, 1.f, 0.f, 0.2f);

    createShaderPrograms();

}

Window::~Window() {
    delete boxElements;
    delete boxVertices;

    glDeleteBuffers(1, &boxElementBuffer);
    glDeleteBuffers(1, &collisionBoxVertexBuffer);
    glDeleteVertexArrays(1, &collisionBoxVertexArray);

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::windowResizeCallback(GLFWwindow* window, int width, int height) {
    winWidth = width, winHeight = height;
    glViewport(0, 0, width, height);
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    switch (action) {
        case GLFW_PRESS:
            KEYS[key] = true;
            break;
        case GLFW_RELEASE:
            KEYS[key] = false;
            break;
        default:
            break;
    }
}

void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    switch(action) {
        case GLFW_PRESS:
            MOUSE_BUTTONS[button] = true;
            break;
        case GLFW_RELEASE:
            MOUSE_BUTTONS[button] = false;
            break;
        default:
            break;
    }
}

void Window::mouseMoveCallback(GLFWwindow* window, double xpos, double ypos) {
    MOUSE_POSITION_X = xpos;
    MOUSE_POSITION_Y = ypos;
}

bool Window::isAlive() {
    return ! glfwWindowShouldClose(window);
}

void Window::setKill() {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Window::showPointer() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::hidePointer() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::clear() {
    glfwSwapBuffers(window);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwPollEvents();
}

void Window::render(Camera3D *c, GameObject2DSprite *s) {
    glViewport(c->viewport.x * winWidth, c->viewport.y * winHeight, c->viewport.w * winWidth, c->viewport.h * winHeight);
    glUseProgram(shaderProgram2D);
    glBindVertexArray(s->vertexArrayObject);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, s->texture);
    int textureLocation = glGetUniformLocation(shaderProgram2D, "inTexture");
    glUniform1i(textureLocation, 0);

    int flipUniformPos = glGetUniformLocation(shaderProgram2D, "flip");
    glUniform1i(flipUniformPos, s->flip);

    int objectTransformLocation = glGetUniformLocation(shaderProgram2D, "objectTransform");
    int viewTransformLocation = glGetUniformLocation(shaderProgram2D, "viewTransform");
    int projectionTransformLocation = glGetUniformLocation(shaderProgram2D, "projection");

    glUniformMatrix4fv(objectTransformLocation, 1, GL_FALSE, glm::value_ptr(s->transform));
    glUniformMatrix4fv(viewTransformLocation, 1, GL_FALSE, glm::value_ptr(c->getTransform()));
    glUniformMatrix4fv(projectionTransformLocation, 1, GL_FALSE, glm::value_ptr(c->projection));

    int animationFrameUniformLocation = glGetUniformLocation(shaderProgram2D, "animationFrame");
    glUniform1i(animationFrameUniformLocation, 0);

    int animationChunkSizeUniformLocation = glGetUniformLocation(shaderProgram2D, "animationChunkSize");
    glUniform1f(animationChunkSizeUniformLocation, 1.f);

    glDrawElements(GL_TRIANGLES, s->numElements(), GL_UNSIGNED_INT, 0);

}

void Window::render(Camera3D *c, GameObject2DAnimatedSprite *s) {
    glViewport(c->viewport.x * winWidth, c->viewport.y * winHeight, c->viewport.w * winWidth, c->viewport.h * winHeight);
    glUseProgram(shaderProgram2D);
    glBindVertexArray(s->vertexArrayObject);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, s->currentTexture());

    int flipUniformPos = glGetUniformLocation(shaderProgram2D, "flip");
    glUniform1i(flipUniformPos, s->flip);

    int objectTransformLocation = glGetUniformLocation(shaderProgram2D, "objectTransform");
    int viewTransformLocation = glGetUniformLocation(shaderProgram2D, "viewTransform");
    int projectionTransformLocation = glGetUniformLocation(shaderProgram2D, "projection");

    glUniformMatrix4fv(objectTransformLocation, 1, GL_FALSE, glm::value_ptr(s->transform));
    glUniformMatrix4fv(viewTransformLocation, 1, GL_FALSE, glm::value_ptr(c->getTransform()));
    glUniformMatrix4fv(projectionTransformLocation, 1, GL_FALSE, glm::value_ptr(c->projection));

    int animationFrameUniformLocation = glGetUniformLocation(shaderProgram2D, "animationFrame");
    glUniform1i(animationFrameUniformLocation, s->currentFrame());

    int animationChunkSizeUniformLocation = glGetUniformLocation(shaderProgram2D, "animationChunkSize");
    glUniform1f(animationChunkSizeUniformLocation, s->currentAnimationChunkSize());

    glDrawElements(GL_TRIANGLES, s->numElements(), GL_UNSIGNED_INT, 0);
}

void Window::render(Camera3D *c, GameObject3DTextured *obj, GameObjectSpotLightSource *light) {
    glViewport(c->viewport.x * winWidth, c->viewport.y * winHeight, c->viewport.w * winWidth, c->viewport.h * winHeight);
    glUseProgram(spotLightShaderProgram);
    glBindVertexArray(obj->vertexArrayObject);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, obj->texture);
    int objectTextureLocation = glGetUniformLocation(spotLightShaderProgram, "inTexture");
    glUniform1i(objectTextureLocation, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    int depthMapTextureLocation = glGetUniformLocation(spotLightShaderProgram, "inDepthMap");
    glUniform1i(depthMapTextureLocation, 1);

    int flipUniformPos = glGetUniformLocation(spotLightShaderProgram, "flip");
    glUniform1i(flipUniformPos, obj->flip);

    int objectTransformLocation = glGetUniformLocation(spotLightShaderProgram, "objectTransform");
    int viewTransformLocation = glGetUniformLocation(spotLightShaderProgram, "viewTransform");
    int projectionTransformLocation = glGetUniformLocation(spotLightShaderProgram, "projection");

    glUniformMatrix4fv(objectTransformLocation, 1, GL_FALSE, glm::value_ptr(obj->transform));
    glUniformMatrix4fv(viewTransformLocation, 1, GL_FALSE, glm::value_ptr(c->getTransform()));
    glUniformMatrix4fv(projectionTransformLocation, 1, GL_FALSE, glm::value_ptr(c->getProjectionTransform()));

    int animationFrameUniformLocation = glGetUniformLocation(spotLightShaderProgram, "animationFrame");
    int animationChunkSizeUniformLocation = glGetUniformLocation(spotLightShaderProgram, "animationChunkSize");

    int lightColorLocation = glGetUniformLocation(spotLightShaderProgram, "lightColor");
    int lightPosLocation = glGetUniformLocation(spotLightShaderProgram, "lightPos");

    int lightViewTransformLocation = glGetUniformLocation(spotLightShaderProgram, "lightViewTransform");
    int lightProjectionTransformLocation = glGetUniformLocation(spotLightShaderProgram, "lightProjectionTransform");

    glUniform1i(animationFrameUniformLocation, 0);
    glUniform1f(animationChunkSizeUniformLocation, 1.f);

    glUniform3fv(lightColorLocation, 1, glm::value_ptr(light->lightColor));
    glUniform3fv(lightPosLocation, 1, glm::value_ptr(light->getPos()));

    glUniformMatrix4fv(lightViewTransformLocation, 1, GL_FALSE, glm::value_ptr(light->getViewTransform()));
    glUniformMatrix4fv(lightProjectionTransformLocation, 1, GL_FALSE, glm::value_ptr(light->getProjectionTransform()));

    glDrawArrays(GL_TRIANGLES, 0, obj->numVertices());

}

void Window::render(Camera3D *c, GameObject3DTextured *obj, GameObjectPointLightSource *light) {
    glViewport(c->viewport.x * winWidth, c->viewport.y * winHeight, c->viewport.w * winWidth, c->viewport.h * winHeight);
    glUseProgram(pointLightShaderProgram);
    glBindVertexArray(obj->vertexArrayObject);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, obj->texture);
    int objectTextureLocation = glGetUniformLocation(pointLightShaderProgram, "inTexture");
    glUniform1i(objectTextureLocation, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubeMap);
    int depthMapTextureLocation = glGetUniformLocation(pointLightShaderProgram, "inDepthMap");
    glUniform1i(depthMapTextureLocation, 1);

    int flipUniformPos = glGetUniformLocation(pointLightShaderProgram, "flip");
    glUniform1i(flipUniformPos, obj->flip);

    int objectTransformLocation = glGetUniformLocation(pointLightShaderProgram, "objectTransform");
    int viewTransformLocation = glGetUniformLocation(pointLightShaderProgram, "viewTransform");
    int projectionTransformLocation = glGetUniformLocation(pointLightShaderProgram, "projection");

    glUniformMatrix4fv(objectTransformLocation, 1, GL_FALSE, glm::value_ptr(obj->transform));
    glUniformMatrix4fv(viewTransformLocation, 1, GL_FALSE, glm::value_ptr(c->getTransform()));
    glUniformMatrix4fv(projectionTransformLocation, 1, GL_FALSE, glm::value_ptr(c->getProjectionTransform()));

    int animationFrameUniformLocation = glGetUniformLocation(pointLightShaderProgram, "animationFrame");
    int animationChunkSizeUniformLocation = glGetUniformLocation(pointLightShaderProgram, "animationChunkSize");

    int lightColorLocation = glGetUniformLocation(pointLightShaderProgram, "lightColor");
    int lightPosLocation = glGetUniformLocation(pointLightShaderProgram, "lightPos");
    int farPlaneLocation = glGetUniformLocation(pointLightShaderProgram, "farPlane");

    glUniform1i(animationFrameUniformLocation, 0);
    glUniform1f(animationChunkSizeUniformLocation, 1.f);

    glUniform3fv(lightColorLocation, 1, glm::value_ptr(light->lightColor));
    glUniform3fv(lightPosLocation, 1, glm::value_ptr(light->getPos()));
    glUniform1f(farPlaneLocation, light->farPlane);

    glDrawArrays(GL_TRIANGLES, 0, obj->numVertices());

}

void Window::render(Camera3D *c, GameObject2DCollisionBox *b) {
    glViewport(c->viewport.x * winWidth, c->viewport.y * winHeight, c->viewport.w * winWidth, c->viewport.h * winHeight);

    glUseProgram(collisionBoxShaderProgram);
    glBindVertexArray(collisionBoxVertexArray);

    int objectTransformLocation = glGetUniformLocation(collisionBoxShaderProgram, "objectTransform");
    int viewTransformLocation = glGetUniformLocation(collisionBoxShaderProgram, "viewTransform");
    int projectionTransformLocation = glGetUniformLocation(collisionBoxShaderProgram, "projection");
    int colorUniformLocation = glGetUniformLocation(collisionBoxShaderProgram, "inColor");

    glUniformMatrix4fv(objectTransformLocation, 1, GL_FALSE, glm::value_ptr(b->getTransform()));
    glUniformMatrix4fv(viewTransformLocation, 1, GL_FALSE, glm::value_ptr(c->getTransform()));
    glUniformMatrix4fv(projectionTransformLocation, 1, GL_FALSE, glm::value_ptr(c->projection));
    glUniform4fv(colorUniformLocation, 1, glm::value_ptr(colliderColor));

    glDrawElements(GL_TRIANGLES, boxElements->size(), GL_UNSIGNED_INT, 0);
}

void Window::render(Camera3D *c, GameObjectSpotLightSource *light) {
    glViewport(c->viewport.x * winWidth, c->viewport.y * winHeight, c->viewport.w * winWidth, c->viewport.h * winHeight);

    glUseProgram(collisionBoxShaderProgram);
    glBindVertexArray(collisionBoxVertexArray);

    int objectTransformLocation = glGetUniformLocation(collisionBoxShaderProgram, "objectTransform");
    int viewTransformLocation = glGetUniformLocation(collisionBoxShaderProgram, "viewTransform");
    int projectionTransformLocation = glGetUniformLocation(collisionBoxShaderProgram, "projection");
    int colorUniformLocation = glGetUniformLocation(collisionBoxShaderProgram, "inColor");

    glUniformMatrix4fv(objectTransformLocation, 1, GL_FALSE, glm::value_ptr(light->getTransform()));
    glUniformMatrix4fv(viewTransformLocation, 1, GL_FALSE, glm::value_ptr(c->transform));
    glUniformMatrix4fv(projectionTransformLocation, 1, GL_FALSE, glm::value_ptr(c->projection));
    glUniform4fv(colorUniformLocation, 1, glm::value_ptr(glm::vec4(light->lightColor, 1.f)));

    glDrawElements(GL_TRIANGLES, boxElements->size(), GL_UNSIGNED_INT, 0);
    
}

void Window::render(Camera3D *c, GameObjectPointLightSource *light) {
    glViewport(c->viewport.x * winWidth, c->viewport.y * winHeight, c->viewport.w * winWidth, c->viewport.h * winHeight);

    glUseProgram(collisionBoxShaderProgram);
    glBindVertexArray(collisionBoxVertexArray);

    int objectTransformLocation = glGetUniformLocation(collisionBoxShaderProgram, "objectTransform");
    int viewTransformLocation = glGetUniformLocation(collisionBoxShaderProgram, "viewTransform");
    int projectionTransformLocation = glGetUniformLocation(collisionBoxShaderProgram, "projection");
    int colorUniformLocation = glGetUniformLocation(collisionBoxShaderProgram, "inColor");

    glUniformMatrix4fv(objectTransformLocation, 1, GL_FALSE, glm::value_ptr(light->getTransform()));
    glUniformMatrix4fv(viewTransformLocation, 1, GL_FALSE, glm::value_ptr(c->transform));
    glUniformMatrix4fv(projectionTransformLocation, 1, GL_FALSE, glm::value_ptr(c->projection));
    glUniform4fv(colorUniformLocation, 1, glm::value_ptr(glm::vec4(light->lightColor, 1.f)));

    glDrawElements(GL_TRIANGLES, boxElements->size(), GL_UNSIGNED_INT, 0);
}

void Window::render(MenuItem* item) {
    glViewport(0, 0, winWidth, winHeight);
    glUseProgram(menuItemShaderProgram);
    glBindVertexArray(item->vertexArrayObject);

    int screenPosLocation = glGetUniformLocation(menuItemShaderProgram, "screenPos");
    int backgroundColorLocation = glGetUniformLocation(menuItemShaderProgram, "backgroundColor");

    glm::vec2 screenPos = glm::vec2(item->screenPos.x, item->screenPos.y);
    glUniform2fv(screenPosLocation, 1, glm::value_ptr(screenPos));
    glUniform3fv(backgroundColorLocation, 1, glm::value_ptr(item->backgroundColor));

    glDrawElements(GL_TRIANGLES, item->numElements(), GL_UNSIGNED_INT, 0);

    // then we have to render some text on top of the box so that the item is complete
    // this might be doable with the same shader program
    // maybe you can combine all the text into one texture using a framebuffer
    // then you can pass that texture into the menuitem shader program
    // and render it using the item and some texture coords
    

}

void Window::createCollisionBoxRenderDependancies() {
    // create the buffers


    boxVertices = new std::vector<float> {
        0.0f, 0.0f, 0.0f,
        0.f, 1.f, 0.f,
        1.f, 1.f, 0.f,
        1.f, 0.f, 0.f,
    };

    boxElements = new std::vector<unsigned int> {
        0, 1, 2,
        2, 3, 0
    };

    collisionBoxVertexBuffer = Renderable::createVertexBuffer(boxVertices);
    glGenVertexArrays(1, &collisionBoxVertexArray);
    glBindVertexArray(collisionBoxVertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, collisionBoxVertexBuffer);
    glGenBuffers(1, &boxElementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boxElementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * boxElements->size(), boxElements->data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0 );
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);

    // create shaders


}

void Window::createShadowMapDependancies() {

    // create a new framebuffer to render our depth map to
    glGenFramebuffers(1, &depthMapFrameBuffer);

    // create the texture for the depth map
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    float shadowBorderColor[] = {1.f, 1.f, 1.f, 1.f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, shadowBorderColor);

    // attach the texture to the framebuffers depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFrameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void Window::createShadowCubeMapDependancies() {
    
    // generate the cubeMap texture
    glGenFramebuffers(1, &depthCubeMapFrameBuffer);
    glGenTextures(1, &depthCubeMap);

    glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubeMap);
    for (unsigned int i = 0; i < 6; i++) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
                SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // bind the cube map texture to the depth buffer
    
    glBindFramebuffer(GL_FRAMEBUFFER, depthCubeMapFrameBuffer);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubeMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


}

void Window::createShaderPrograms() {
    // create shaders for 2D gameObjects
    shaderProgram2D = Renderable::createBasicShaderProgram("basic2DVert.vert", "basic2DFrag.frag");
    collisionBoxShaderProgram = Renderable::createBasicShaderProgram("basicSolidColorVert.vert", "basicSolidColorFrag.frag");

    menuItemShaderProgram = Renderable::createBasicShaderProgram("menuItem.vert", "menuItem.frag");

    // create shader programs that will render to framebuffers for depth mapping
    shadowMapShaderProgram = Renderable::createBasicShaderProgram("shadowVert.vert", "emptyFrag.frag");
    cubeMapShaderProgram = Renderable::createBasicShaderProgramWithGeometry("cubeMapShader.vert", "cubeMapShader.geom", "cubeMapShader.frag");

    // create shader programs that will render with a light
    pointLightShaderProgram = Renderable::createBasicShaderProgram("texturedPointLight.vert", "texturedPointLight.frag");
    spotLightShaderProgram = Renderable::createBasicShaderProgram("texturedSpotLight.vert", "texturedSpotLight.frag");
}

void Window::renderShadows(GameObject3DTextured *obj, GameObjectSpotLightSource *light) {

    //glClear(GL_DEPTH_BUFFER_BIT);

    glUseProgram(shadowMapShaderProgram);
    glBindVertexArray(obj->vertexArrayObject);

    int lightViewLocation = glGetUniformLocation(shadowMapShaderProgram, "lightViewTransform");
    int lightProjectionLocation = glGetUniformLocation(shadowMapShaderProgram, "lightProjectionTransform");
    int objectTransformLocation = glGetUniformLocation(shadowMapShaderProgram, "objectTransform");
    
    glUniformMatrix4fv(lightViewLocation, 1, GL_FALSE, glm::value_ptr(light->getViewTransform()));
    glUniformMatrix4fv(lightProjectionLocation, 1, GL_FALSE, glm::value_ptr(light->getProjectionTransform()));
    glUniformMatrix4fv(objectTransformLocation, 1, GL_FALSE, glm::value_ptr(obj->getTransform()));

    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFrameBuffer);

    glDrawArrays(GL_TRIANGLES, 0, obj->numVertices());

    glBindFramebuffer(GL_FRAMEBUFFER, 0);


}

void Window::renderShadows(GameObject3DTextured* obj, GameObjectPointLightSource *light) {
    glUseProgram(cubeMapShaderProgram);
    glBindVertexArray(obj->vertexArrayObject);

    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubeMap);

    int objectTransformLocation = glGetUniformLocation(cubeMapShaderProgram, "objectTransform");
    int lightViewTransformsLocation = glGetUniformLocation(cubeMapShaderProgram, "lightViewTransforms");
    int lightProjectionTransformLocation = glGetUniformLocation(cubeMapShaderProgram, "lightProjectionTransform");
    int farPlaneLocation = glGetUniformLocation(cubeMapShaderProgram, "farPlane");

    glUniformMatrix4fv(objectTransformLocation, 1, GL_FALSE, glm::value_ptr(obj->getTransform()));
    glUniformMatrix4fv(lightViewTransformsLocation, 6, GL_FALSE, glm::value_ptr(light->getViewTransforms()[0]));
    glUniformMatrix4fv(lightProjectionTransformLocation, 1, GL_FALSE, glm::value_ptr(light->getProjectionTransform()));
    glUniform1f(farPlaneLocation, light->farPlane);

    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthCubeMapFrameBuffer);

    glDrawArrays(GL_TRIANGLES, 0, obj->numVertices());

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Window::clearShadow() {
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFrameBuffer);
    glClear(GL_DEPTH_BUFFER_BIT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthCubeMapFrameBuffer);
    glClear(GL_DEPTH_BUFFER_BIT);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

}
