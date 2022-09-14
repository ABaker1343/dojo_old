#include "headers/window.hpp"
#include "headers/gameObject3DTextured.hpp"
#include "headers/renderable.hpp"
#include <glm/ext/quaternion_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace dojo {

bool Window::KEYS[KEYS_SIZE];

Window::Window(int width, int height, const char* name) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    window = glfwCreateWindow(
            width, height, name,
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
    glUseProgram(s->shaderProgram);
    glBindVertexArray(s->vertexArrayObject);

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
    glUseProgram(s->shaderProgram);
    glBindVertexArray(s->vertexArrayObject);

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

void Window::render(Camera3D *c, GameObject3DTextured *obj) {
    glUseProgram(obj->shaderProgram);
    glBindVertexArray(obj->vertexArrayObject);

    glBindTexture(GL_TEXTURE_2D, obj->texture);

    int flipUniformPos = glGetUniformLocation(obj->shaderProgram, "flip");
    glUniform1i(flipUniformPos, obj->flip);

    int objectTransformLocation = glGetUniformLocation(obj->shaderProgram, "objectTransform");
    int viewTransformLocation = glGetUniformLocation(obj->shaderProgram, "viewTransform");
    int projectionTransformLocation = glGetUniformLocation(obj->shaderProgram, "projection");

    glUniformMatrix4fv(objectTransformLocation, 1, GL_FALSE, glm::value_ptr(obj->transform));
    glUniformMatrix4fv(viewTransformLocation, 1, GL_FALSE, glm::value_ptr(c->transform));
    glUniformMatrix4fv(projectionTransformLocation, 1, GL_FALSE, glm::value_ptr(c->projection));

    int animationFrameUniformLocation = glGetUniformLocation(obj->shaderProgram, "animationFrame");
    int animationChunkSizeUniformLocation = glGetUniformLocation(obj->shaderProgram, "animationChunkSize");

    int lightColorLocation = glGetUniformLocation(obj->shaderProgram, "lightColor");
    int lightPosLocation = glGetUniformLocation(obj->shaderProgram, "lightPos");

    glUniform1i(animationFrameUniformLocation, 0);
    glUniform1f(animationChunkSizeUniformLocation, 1.f);

    glUniform3fv(lightColorLocation, 1, glm::value_ptr(colliderColor));
    glUniform3fv(lightPosLocation, 1, glm::value_ptr(glm::vec3(10.f, 10.f, 0.f)));

    //glDrawElements(GL_TRIANGLES, obj->numElements(), GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, obj->numVertices());

}

void Window::render(Camera3D *c, GameObject2DCollisionBox *b) {

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

    collisionBoxShaderProgram = Renderable::createBasicShaderProgram("src/shaders/basicSolidColorVert.vert", "src/shaders/basicSolidColorFrag.frag");

}

}
