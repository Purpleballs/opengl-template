#include <glad/glad.h>  // if you use glad; must come before GLFW
#include <GLFW/glfw3.h> //for input but might not actually want to include this here

#include "Application.h"
#include "core/window.h"
#include <iostream>
#include <string>
//#include "core/camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "core/RenderCommand.h"
#include "core/Geometry.h"
#include "core/shader_s.h"

Geometry quad;
Shader shader;
GLuint debugVAO = 0;
int SCR_WIDTH = 1280;
int SCR_HEIGHT = 720; // make getter

float lastX;
float lastY;
bool firstMouse = true;
void Application::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// Add a static wrapper for the mouse callback
static void MouseCallbackWrapper(GLFWwindow* window, double xpos, double ypos)
{
    // Retrieve the Application instance from the window user pointer
    void* userPtr = glfwGetWindowUserPointer(window);
    if (userPtr)
    {
        static_cast<Application*>(userPtr)->mouse_callback(window, xpos, ypos);
    }
}

void Application::init()
{
    // Use the static wrapper as the callback
    glfwSetWindowUserPointer(window.getHandle(), this);
    glfwSetCursorPosCallback(window.getHandle(), MouseCallbackWrapper);
    std::cout << "Application Init\n";
	RenderCommand::Init();
	quad = Geometry::Sphere(20,20);
   // glGenVertexArrays(1, &debugVAO); 
    //glBindVertexArray(debugVAO);
    //glBindVertexArray(0);
    shader =  Shader("asset/shader/basicvert.vert", "asset/shader/basicfrag.frag");
}

void Application::update()
{
    shader.use();
	glfwGetWindowSize(window.getHandle(), &SCR_WIDTH, &SCR_HEIGHT); //move this to callback in window class and make getters
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    // world transformation
    glm::mat4 model = glm::mat4(1.0f);
    shader.setMat4("model", model);
}

void Application::beginRender()
{
	RenderCommand::Clear(0.1f, 0.1f, 0.15f, 1.0f);
}

void Application::render()
{
	shader.use();
    //shader.setMat4("uMVP", glm::mat4(1.0f));
    //shader.setVec3("aPos", 1.0f, 1.0f, 0.0f);
	//glBindVertexArray(debugVAO);
	//glDrawArrays(GL_TRIANGLES, 0, 3); 
	//glBindVertexArray(0);
	quad.Draw();
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
        std::string title = window.getTitle() + " | FPS: " + std::to_string(frameCount);
        glfwSetWindowTitle(window.getHandle(), title.c_str());

        frameCount = 0;
        timeAccumulator = 0.0f;
    }

    dt = deltaTime;
}


void Application::run()
{
    while (!window.shouldClose())
    {
        updateDeltaTime();
        window.pollEvents();
        handleInput(window.getHandle());
        update();
        beginRender();
        render();
        window.swapBuffers();
    }
}
