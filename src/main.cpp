#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "app/Application.h"
#include "core/window.h"


const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

int main()
{
	Window window(SCR_WIDTH, SCR_HEIGHT, "OpenGL Sandbox");
    Application app(window);
    app.init();
    app.run();
    return 0;
}
