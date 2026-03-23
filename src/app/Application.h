#pragma once

#include "core/camera.h"

// Forward declarations
struct GLFWwindow;
class Window;

class Application {
public:
	
	Application(Window& window) : window(window){ init(); }
	void run();
    void update();
	void beginRender();
    void render();
	void handleInput(GLFWwindow* window);
	void updateDeltaTime();
	float getdeltaTime() const { return dt; }
	void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

private:
	void init(); //calling this in constructor not sure if that's a good idea.
	Camera camera;
	Window& window;
	
	int frameCount = 0;
	float timeAccumulator = 0.0f;
	float dt = 0.0f;
	float lastFrame = 0.0f;
};
