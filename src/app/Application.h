#pragma once

#include "core/camera.h"

struct GLFWwindow;
class Window;

class Application {
public:
	Application(Window& window) : window(window){}
    void init();
    void update();
	void beginRender();
    void render();
	void handleInput(GLFWwindow* window);
	
	float getdeltaTime() const { return dt; }

private:
	Camera camera;
	Window& window;
	void updateDeltaTime();
	int frameCount = 0;
	float timeAccumulator = 0.0f;
	float dt = 0.0f;
	float lastFrame = 0.0f;
};
