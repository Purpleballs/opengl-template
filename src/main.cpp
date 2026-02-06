#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "core/camera.h"
#include "app/Application.h"
#include "core/window.h"


const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

int main()
{
	Window window(SCR_WIDTH, SCR_HEIGHT, "OpenGL App");

    glEnable(GL_DEPTH_TEST);

    Application app;
    app.init();

    while (!window.shouldClose())
    {
        window.pollEvents();
        window.updateDeltaTime();
        app.handleInput(window.getHandle(), window.getdeltaTime());

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        app.update(window.getdeltaTime());
        app.render();

        window.swapBuffers();
        
    }
    return 0;
}
