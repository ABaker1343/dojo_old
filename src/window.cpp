#include "headers/window.hpp"

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

    glViewport(0, 0, width, height);
    
    glfwSetFramebufferSizeCallback(window, windowResizeCallback);
    glfwSetKeyCallback(window, keyCallback);
    

}

Window::~Window() {
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

void Window::clear() {
    glfwSwapBuffers(window);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwPollEvents();
}

void Window::render2D(Camera2D *c, GameObject2DSprite *s) {
    glUseProgram(s->shaderProgram);
    glBindVertexArray(s->vertexArrayObject);

    glBindTexture(GL_TEXTURE_2D, s->texture);

    int flipUniformPos = glGetUniformLocation(s->shaderProgram, "flip");
    glUniform1i(flipUniformPos, s->flip);

    int worldPosUniformLocation = glGetUniformLocation(s->shaderProgram, "worldPos");
    glUniform3fv(worldPosUniformLocation, 1, glm::value_ptr(s->pos));

    int scaleUniformLocation = glGetUniformLocation(s->shaderProgram, "objectScale");
    glUniform3fv(scaleUniformLocation, 1, glm::value_ptr(s->scale));

    int cameraPosUniformLocation = glGetUniformLocation(s->shaderProgram, "cameraPos");
    glUniform3fv(cameraPosUniformLocation, 1, glm::value_ptr(c->pos));

    int cameraScaleUniformLocation = glGetUniformLocation(s->shaderProgram, "cameraScale");
    glUniform3fv(cameraScaleUniformLocation, 1, glm::value_ptr(c->scale));

    int animationFrameUniformLocation = glGetUniformLocation(s->shaderProgram, "animationFrame");
    glUniform1i(animationFrameUniformLocation, 0);

    int animationChunkSizeUniformLocation = glGetUniformLocation(s->shaderProgram, "animationChunkSize");
    glUniform1i(animationChunkSizeUniformLocation, 1.0f);

    glDrawElements(GL_TRIANGLES, s->numElements(), GL_UNSIGNED_INT, 0);
}

void Window::render2D(Camera2D *c, GameObject2DAnimatedSprite *s) {
    glUseProgram(s->shaderProgram);
    glBindVertexArray(s->vertexArrayObject);

    glBindTexture(GL_TEXTURE_2D, s->currentTexture());

    int flipUniformPos = glGetUniformLocation(s->shaderProgram, "flip");
    glUniform1i(flipUniformPos, s->flip);

    int worldPosUniformLocation = glGetUniformLocation(s->shaderProgram, "worldPos");
    glUniform3fv(worldPosUniformLocation, 1, glm::value_ptr(s->pos));

    int scaleUniformLocation = glGetUniformLocation(s->shaderProgram, "objectScale");
    glUniform3fv(scaleUniformLocation, 1, glm::value_ptr(s->scale));

    int cameraPosUniformLocation = glGetUniformLocation(s->shaderProgram, "cameraPos");
    glUniform3fv(cameraPosUniformLocation, 1, glm::value_ptr(c->pos));

    int cameraScaleUniformLocation = glGetUniformLocation(s->shaderProgram, "cameraScale");
    glUniform3fv(cameraScaleUniformLocation, 1, glm::value_ptr(c->scale));

    int animationFrameUniformLocation = glGetUniformLocation(s->shaderProgram, "animationFrame");
    glUniform1i(animationFrameUniformLocation, s->currentFrame());

    int animationChunkSizeUniformLocation = glGetUniformLocation(s->shaderProgram, "animationChunkSize");
    glUniform1f(animationChunkSizeUniformLocation, s->currentAnimationChunkSize());

    glDrawElements(GL_TRIANGLES, s->numElements(), GL_UNSIGNED_INT, 0);
}

}
