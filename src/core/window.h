#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "errorReporting.h"
class Window {
public:
    Window(const char* title) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		m_Title = title;
        handle = glfwCreateWindow(1280, 720, title, nullptr, nullptr);
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

        enableReportGlErrors(); //probably should be called elsewere //is this even working

        // This allows us to get our C++ object back inside static callbacks
        glfwSetWindowUserPointer(handle, this);

        // Set static callback
        glfwSetFramebufferSizeCallback(handle, framebuffer_size_callback);
    }

    ~Window() {
        if(handle)
            glfwDestroyWindow(handle);
		glfwTerminate(); //move this to Application destructor if you want to support multiple windows in the future
    }

    bool shouldClose() { return glfwWindowShouldClose(handle); }
    void swapBuffers() { glfwSwapBuffers(handle); }
    void pollEvents() { glfwPollEvents(); }
    
    void printresolution() const {
        int width, height;
        glfwGetFramebufferSize(handle, &width, &height);
        std::cout << "Current resolution: " << width << "x" << height << std::endl;
	}
    void getresolution(int& width, int& height) const {
        glfwGetFramebufferSize(handle, &width, &height);
	}
    //getters
    GLFWwindow* getHandle() const { return handle; }
    const std::string& getTitle() const { return m_Title; }
private:
    GLFWwindow* handle;
	std::string m_Title;
	static int m_Width;
	static int m_Height;
    // Static wrapper needed for GLFW (C-style)
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
		std::cout << "Window resized: " << width << "x" << height << std::endl;
		m_Width = width;
		m_Height = height;
        // If you want your Application to respond to resize, 
        // you would retrieve it here via UserPointer
    }

};

