#pragma once
#include <vector>
#include <glad/glad.h>

class Geometry
{
public:
    Geometry() = default;

    Geometry(const std::vector<float>& vertices,
        const std::vector<unsigned int>& indices,
        int stride);

    ~Geometry();

    Geometry(const Geometry&) = delete;
    Geometry& operator=(const Geometry&) = delete;

    Geometry(Geometry&& other) noexcept;
    Geometry& operator=(Geometry&& other) noexcept;

    void Draw() const;

    static Geometry Cube();
    static Geometry FullscreenQuad();
    static Geometry Sphere(int segments, int rings);
    static Geometry Capsule(float radius, float height, int segments, int rings);

private:
    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ebo = 0;

    GLsizei indexCount = 0;
};