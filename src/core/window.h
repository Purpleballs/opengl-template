#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class Window {
public:
    Window(int width, int height, const char* title) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!handle) {
            std::cout << "Failed to create window" << std::endl;
            glfwTerminate();
			throw std::runtime_error("Failed to create GLFW window");
        }

        glfwMakeContextCurrent(handle);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD\n";
            throw std::runtime_error("Failed to initialize GLAD");
        }

        // This allows us to get our C++ object back inside static callbacks
        glfwSetWindowUserPointer(handle, this);

        // Set static callback
        glfwSetFramebufferSizeCallback(handle, framebuffer_size_callback);
    }

    ~Window() {
        if(handle)
            glfwDestroyWindow(handle);
        glfwTerminate();
    }

    bool shouldClose() { return glfwWindowShouldClose(handle); }
    void swapBuffers() { glfwSwapBuffers(handle); }
    void pollEvents() { glfwPollEvents(); }
    
    //getters
    GLFWwindow* getHandle() const { return handle; }
    float getdeltaTime() const { return deltaTime; } 

    void updateDeltaTime() {
        float currentFrame = (float)glfwGetTime();
        float dt = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Logic to update title bar FPS every 1 second (cleaner than every 120 frames)
        frameCount++;
        timeAccumulator += dt;

        if (timeAccumulator >= 1.0f) {
            std::string title = "OpenGL App | FPS: " + std::to_string(frameCount);
            glfwSetWindowTitle(handle, title.c_str());

            // Reset for next second
            frameCount = 0;
            timeAccumulator = 0.0f;
        }

        deltaTime = dt;
    }
private:
    GLFWwindow* handle;
    float lastFrame = 0.0f;
	int frameCount = 0;
	float timeAccumulator = 0.0f;
    float deltaTime = 0.0f;

    // Static wrapper needed for GLFW (C-style)
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
		//std::cout << "Window resized: " << width << "x" << height << std::endl;

        // If you want your Application to respond to resize, 
        // you would retrieve it here via UserPointer
    }
};

