#include <glad/glad.h>  // if you use glad; must come before GLFW
#include <GLFW/glfw3.h> //for events but might not actually want to include this here

#include "Application.h"
#include "core/window.h"
#include <iostream>
#include <string>
//#include "core/camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void Application::init()
{
    std::cout << "Application Init\n";
    glEnable(GL_DEPTH_TEST);
}

void Application::update()
{
    updateDeltaTime();
}
void Application::beginRender()
{
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Application::render()
{
	// Placeholder for rendering code
}

void Application::handleInput(GLFWwindow* window)
{
      if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
          glfwSetWindowShouldClose(window, true); 
      if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
          camera.ProcessKeyboard(FORWARD, dt); 
      if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
          camera.ProcessKeyboard(BACKWARD, dt); 
      if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
          camera.ProcessKeyboard(LEFT, dt); 
      if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
          camera.ProcessKeyboard(RIGHT, dt); 
      if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
          camera.ProcessKeyboard(UP, dt); 
      if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) 
          camera.ProcessKeyboard(DOWN, dt); 
}
void Application::updateDeltaTime() {
    float currentFrame = (float)glfwGetTime();
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    frameCount++;
    timeAccumulator += deltaTime;
    if (timeAccumulator >= 1.0f) {
        std::string title = "OpenGL App | FPS: " + std::to_string(frameCount);
        glfwSetWindowTitle(window.getHandle(), title.c_str());

        frameCount = 0;
        timeAccumulator = 0.0f;
    }

    dt = deltaTime;
}
