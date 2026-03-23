#include "app/Application.h"
#include "core/window.h"
int main()
{
	Window window("OpenGL Sandbox");
    { // Create application in its own scope so it gets destroyed before the window (important for cleanup order
        Application app(window);
		// app.init(); //doing this in constructor for now but might want to change that later
        app.run();
    }
    return 0;
}
