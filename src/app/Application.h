#pragma once

#include "core/camera.h"
struct GLFWwindow;

class Application {
public:
    void init();
    void update(float dt);
    void render();
	void handleInput(GLFWwindow* window, float deltaTime);

private:
	Camera camera;

};
