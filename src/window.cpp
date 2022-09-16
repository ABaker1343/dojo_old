#include "headers/window.hpp"
#include "headers/gameObject3DTextured.hpp"
#include "headers/renderable.hpp"
#include <glm/ext/quaternion_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace dojo {

bool Window::KEYS[KEYS_SIZE];
int Window::winHeight, Window::winWidth;

Window::Window(int width, int height, const char* name) {
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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("failed to load opengl functions");
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    // allow color blending

    glViewport(0, 0, width, height);
    
    glfwSetFramebufferSizeCallback(window, windowResizeCallback);
    glfwSetKeyCallback(window, keyCallback);
    
    createShadowMapDependancies();

    createCollisionBoxRenderDependancies();
    colliderColor = glm::vec4(0.f, 1.f, 0.f, 0.2f);

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
    if (action == GLFW_PRESS) {
        KEYS[key] = true;
    }
    if (action == GLFW_RELEASE) {
        KEYS[key] = false;
    }
}

bool Window::isAlive() {
    return ! glfwWindowShouldClose(window);
}

void Window::setKill() {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Window::clear() {
    glfwSwapBuffers(window);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwPollEvents();
}

void Window::render(Camera3D *c, GameObject2DSprite *s) {
    glViewport(c->viewport.x * winWidth, c->viewport.y * winHeight, c->viewport.w * winWidth, c->viewport.h * winHeight);
    glUseProgram(s->shaderProgram);
    glBindVertexArray(s->vertexArrayObject);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, s->texture);

    int flipUniformPos = glGetUniformLocation(s->shaderProgram, "flip");
    glUniform1i(flipUniformPos, s->flip);

    int objectTransformLocation = glGetUniformLocation(s->shaderProgram, "objectTransform");
    int viewTransformLocation = glGetUniformLocation(s->shaderProgram, "viewTransform");
    int projectionTransformLocation = glGetUniformLocation(s->shaderProgram, "projection");

    glUniformMatrix4fv(objectTransformLocation, 1, GL_FALSE, glm::value_ptr(s->transform));
    glUniformMatrix4fv(viewTransformLocation, 1, GL_FALSE, glm::value_ptr(c->transform));
    glUniformMatrix4fv(projectionTransformLocation, 1, GL_FALSE, glm::value_ptr(c->projection));

    int animationFrameUniformLocation = glGetUniformLocation(s->shaderProgram, "animationFrame");
    glUniform1i(animationFrameUniformLocation, 0);

    int animationChunkSizeUniformLocation = glGetUniformLocation(s->shaderProgram, "animationChunkSize");
    glUniform1f(animationChunkSizeUniformLocation, 1.f);

    glDrawElements(GL_TRIANGLES, s->numElements(), GL_UNSIGNED_INT, 0);

}

void Window::render(Camera3D *c, GameObject2DAnimatedSprite *s) {
    glViewport(c->viewport.x * winWidth, c->viewport.y * winHeight, c->viewport.w * winWidth, c->viewport.h * winHeight);
    glUseProgram(s->shaderProgram);
    glBindVertexArray(s->vertexArrayObject);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, s->currentTexture());

    int flipUniformPos = glGetUniformLocation(s->shaderProgram, "flip");
    glUniform1i(flipUniformPos, s->flip);

    int objectTransformLocation = glGetUniformLocation(s->shaderProgram, "objectTransform");
    int viewTransformLocation = glGetUniformLocation(s->shaderProgram, "viewTransform");
    int projectionTransformLocation = glGetUniformLocation(s->shaderProgram, "projection");

    glUniformMatrix4fv(objectTransformLocation, 1, GL_FALSE, glm::value_ptr(s->transform));
    glUniformMatrix4fv(viewTransformLocation, 1, GL_FALSE, glm::value_ptr(c->transform));
    glUniformMatrix4fv(projectionTransformLocation, 1, GL_FALSE, glm::value_ptr(c->projection));

    int animationFrameUniformLocation = glGetUniformLocation(s->shaderProgram, "animationFrame");
    glUniform1i(animationFrameUniformLocation, s->currentFrame());

    int animationChunkSizeUniformLocation = glGetUniformLocation(s->shaderProgram, "animationChunkSize");
    glUniform1f(animationChunkSizeUniformLocation, s->currentAnimationChunkSize());

    glDrawElements(GL_TRIANGLES, s->numElements(), GL_UNSIGNED_INT, 0);
}

void Window::render(Camera3D *c, GameObject3DTextured *obj, GameObjectSpotLightSource *light) {
    glViewport(c->viewport.x * winWidth, c->viewport.y * winHeight, c->viewport.w * winWidth, c->viewport.h * winHeight);
    glUseProgram(obj->shaderProgram);
    glBindVertexArray(obj->vertexArrayObject);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, obj->texture);
    //glBindTexture(GL_TEXTURE_2D, depthMap);
    int objectTextureLocation = glGetUniformLocation(obj->shaderProgram, "inTexture");
    glUniform1i(objectTextureLocation, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    int depthMapTextureLocation = glGetUniformLocation(obj->shaderProgram, "inDepthMap");
    glUniform1i(depthMapTextureLocation, 1);

    int flipUniformPos = glGetUniformLocation(obj->shaderProgram, "flip");
    glUniform1i(flipUniformPos, obj->flip);

    int objectTransformLocation = glGetUniformLocation(obj->shaderProgram, "objectTransform");
    int viewTransformLocation = glGetUniformLocation(obj->shaderProgram, "viewTransform");
    int projectionTransformLocation = glGetUniformLocation(obj->shaderProgram, "projection");

    glUniformMatrix4fv(objectTransformLocation, 1, GL_FALSE, glm::value_ptr(obj->transform));
    glUniformMatrix4fv(viewTransformLocation, 1, GL_FALSE, glm::value_ptr(c->getTransform()));
    glUniformMatrix4fv(projectionTransformLocation, 1, GL_FALSE, glm::value_ptr(c->getProjectionTransform()));

    int animationFrameUniformLocation = glGetUniformLocation(obj->shaderProgram, "animationFrame");
    int animationChunkSizeUniformLocation = glGetUniformLocation(obj->shaderProgram, "animationChunkSize");

    int lightColorLocation = glGetUniformLocation(obj->shaderProgram, "lightColor");
    int lightPosLocation = glGetUniformLocation(obj->shaderProgram, "lightPos");

    int lightViewTransformLocation = glGetUniformLocation(obj->shaderProgram, "lightViewTransform");
    int lightProjectionTransformLocation = glGetUniformLocation(obj->shaderProgram, "lightProjectionTransform");

    glUniform1i(animationFrameUniformLocation, 0);
    glUniform1f(animationChunkSizeUniformLocation, 1.f);

    glUniform3fv(lightColorLocation, 1, glm::value_ptr(light->lightColor));
    glUniform3fv(lightPosLocation, 1, glm::value_ptr(light->getPos()));

    glUniformMatrix4fv(lightViewTransformLocation, 1, GL_FALSE, glm::value_ptr(light->getViewTransform()));
    glUniformMatrix4fv(lightProjectionTransformLocation, 1, GL_FALSE, glm::value_ptr(light->getProjectionTransform()));

    //glDrawElements(GL_TRIANGLES, obj->numElements(), GL_UNSIGNED_INT, 0);
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
    glUniformMatrix4fv(viewTransformLocation, 1, GL_FALSE, glm::value_ptr(c->transform));
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

    collisionBoxShaderProgram = Renderable::createBasicShaderProgram("basicSolidColorVert.vert", "basicSolidColorFrag.frag");

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

    shadowMapShaderProgram = Renderable::createBasicShaderProgram("shadowVert.vert", "emptyFrag.frag");
}

void Window::renderShadows(GameObject3DTextured *obj, GameObjectSpotLightSource *light) {

    //glClear(GL_DEPTH_BUFFER_BIT);

    glUseProgram(shadowMapShaderProgram);

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

void Window::clearShadow() {
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFrameBuffer);
    glClear(GL_DEPTH_BUFFER_BIT);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

}
