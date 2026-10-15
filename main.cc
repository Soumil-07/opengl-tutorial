#include <cstddef>
#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GlfwWrapper.h"
#include "Model.h"
#include "Shader.h"
#include "glm/detail/func_trigonometric.hpp"
#include "glm/detail/type_vec3.hpp"
#include "include/stb_img.h"

glm::vec3 cameraPos(0.f, 0.5f, 16.f);
glm::vec3 cameraFront(0.f, 0.f, -1.f);
glm::vec3 cameraUp(0.f, 1.f, 0.f);

float deltaTime = 0.f;
float lastFrame = 0.f;

float fov = 25.0;

glm::vec3 lightPos = glm::vec3(0.4f, 0.3, 2.0f);

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    const float cameraSpeed = 2.5f * deltaTime;
    glm::vec3 right = glm::normalize(glm::cross(cameraFront, cameraUp));

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += cameraSpeed * right;
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= cameraSpeed * right;
    else if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
        cameraPos = glm::vec3(0.f, 0.f, 3.f);
}

int main()
{
    GlfwWrapper wrapper;
    wrapper.init();

    if (wrapper.setupWindow(800, 600) == -1)
        return -1;

    // tell stb_img to flip textures on y axis 
    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);
    Shader modelShader("./shaders/model.vs", "./shaders/model.fs");
    Model backpackModel("./assets/backpack/backpack.obj");

    while(!glfwWindowShouldClose(wrapper.window))
    {
        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;

        processInput(wrapper.window);

        // render
        glClearColor(0.05f, 0.05f, 0.05f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        modelShader.use();

        glm::mat4 projection = glm::perspective(glm::radians(35.f), (float)800 / (float)600, 0.1f, 100.f);
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        modelShader.setMat4("projection", projection);
        modelShader.setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(45.f), glm::vec3(0.5f, 0.f, 0.f));
        // model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        modelShader.setMat4("model", model);
        backpackModel.Draw(modelShader);

        glfwSwapBuffers(wrapper.window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
