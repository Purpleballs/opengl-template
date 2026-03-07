#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "app/Application.h"
#include "core/window.h"


const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

int main()
{
	Window window(SCR_WIDTH, SCR_HEIGHT, "OpenGL App");
    Application app;
    app.init();

    while (!window.shouldClose())
    {
        window.pollEvents();
        window.updateDeltaTime();
        app.handleInput(window.getHandle(), window.getdeltaTime());
        app.update(window.getdeltaTime());
        app.render();
        window.swapBuffers();    
    }
    return 0;
}
