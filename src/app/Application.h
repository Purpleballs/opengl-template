#pragma once

#include "core/camera.h"

// Forward declarations
struct GLFWwindow;
class Window;

class Application {
public:
	Application(Window& window) : window(window){}
    void init();
	void run();
    void update();
	void beginRender();
    void render();
	void handleInput(GLFWwindow* window);
	void updateDeltaTime();
	float getdeltaTime() const { return dt; }

private:
	Camera camera;
	Window& window;
	
	int frameCount = 0;
	float timeAccumulator = 0.0f;
	float dt = 0.0f;
	float lastFrame = 0.0f;
};
