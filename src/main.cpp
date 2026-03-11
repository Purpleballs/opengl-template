#include "app/Application.h"
#include "core/window.h"

int main()
{
	Window window("OpenGL Sandbox");
    Application app(window);
    app.init();
    app.run();
    return 0;
}
