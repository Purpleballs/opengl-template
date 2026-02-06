#include "Application.h"
#include <iostream>
#include <GLFW/glfw3.h>

void Application::init()
{
    std::cout << "Application Init\n";

}

void Application::update(float dt)
{
	
}

void Application::render()
{
}

void Application::handleInput(GLFWwindow* window, float dt)
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
