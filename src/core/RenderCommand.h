#pragma once

#include <glad/glad.h>

namespace RenderCommand
{


    inline void SetClearColor(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
    }

    inline void Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    inline void EnableDepthTest(bool enabled)
    {
		//bool depthTestEnabled ...
        if (enabled) glEnable(GL_DEPTH_TEST);
        else glDisable(GL_DEPTH_TEST);
    }

    inline void SetViewport(int x, int y, int width, int height)
    {
        glViewport(x, y, width, height);
    }

    inline void Init()
    {
        EnableDepthTest(true);
        // add KHR_debug setup here in debug builds if desired
    }
}
