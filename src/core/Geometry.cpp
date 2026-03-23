#include "Geometry.h"
constexpr float M_PI = 3.14159265358979323846f;
// ---------------- CONSTRUCTOR ----------------

Geometry::Geometry(const std::vector<float>& vertices,
    const std::vector<unsigned int>& indices,
    int stride)
{
    indexCount = (GLsizei)indices.size();

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
        vertices.size() * sizeof(float),
        vertices.data(),
        GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(unsigned int),
        indices.data(),
        GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // normal
    if (stride >= 6)
    {
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    // uv
    if (stride >= 8)
    {
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
}

// ---------------- DESTRUCTOR ----------------

Geometry::~Geometry()
{
    if (ebo) glDeleteBuffers(1, &ebo);
    if (vbo) glDeleteBuffers(1, &vbo);
    if (vao) glDeleteVertexArrays(1, &vao);
}

// ---------------- MOVE CONSTRUCTOR ----------------

Geometry::Geometry(Geometry&& other) noexcept
{
    vao = other.vao;
    vbo = other.vbo;
    ebo = other.ebo;
    indexCount = other.indexCount;

    other.vao = 0;
    other.vbo = 0;
    other.ebo = 0;
    other.indexCount = 0;
}

// ---------------- MOVE ASSIGNMENT ----------------

Geometry& Geometry::operator=(Geometry&& other) noexcept
{
    if (this != &other)
    {
        // Clean up existing resources
        if (ebo) glDeleteBuffers(1, &ebo);
        if (vbo) glDeleteBuffers(1, &vbo);
        if (vao) glDeleteVertexArrays(1, &vao);

        // Transfer ownership
        vao = other.vao;
        vbo = other.vbo;
        ebo = other.ebo;
        indexCount = other.indexCount;

        // Reset source
        other.vao = 0;
        other.vbo = 0;
        other.ebo = 0;
        other.indexCount = 0;
    }
    return *this;
}

// ---------------- DRAW ----------------

void Geometry::Draw() const
{
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

// ---------------- FACTORIES ----------------

Geometry Geometry::FullscreenQuad()
{
    std::vector<float> vertices =
    {
        -1.f,-1.f,0.f, 0.f,0.f,
         1.f,-1.f,0.f, 1.f,0.f,
         1.f, 1.f,0.f, 1.f,1.f,
        -1.f, 1.f,0.f, 0.f,1.f
    };

    std::vector<unsigned int> indices =
    {
        0,1,2,
        2,3,0
    };

    return Geometry(vertices, indices, 5);
}

Geometry Geometry::Cube()
{
    std::vector<float> v =
    {
        // Front
        -1,-1, 1,  0,0,1,  0,0,
         1,-1, 1,  0,0,1,  1,0,
         1, 1, 1,  0,0,1,  1,1,
        -1, 1, 1,  0,0,1,  0,1,

        // Back
        -1,-1,-1,  0,0,-1, 1,0,
        -1, 1,-1,  0,0,-1, 1,1,
         1, 1,-1,  0,0,-1, 0,1,
         1,-1,-1,  0,0,-1, 0,0,

         // Left
         -1,-1,-1, -1,0,0, 0,0,
         -1,-1, 1, -1,0,0, 1,0,
         -1, 1, 1, -1,0,0, 1,1,
         -1, 1,-1, -1,0,0, 0,1,

         // Right
          1,-1,-1,  1,0,0, 1,0,
          1, 1,-1,  1,0,0, 1,1,
          1, 1, 1,  1,0,0, 0,1,
          1,-1, 1,  1,0,0, 0,0,

          // Top
          -1, 1,-1,  0,1,0, 0,1,
          -1, 1, 1,  0,1,0, 0,0,
           1, 1, 1,  0,1,0, 1,0,
           1, 1,-1,  0,1,0, 1,1,

           // Bottom
           -1,-1,-1,  0,-1,0, 1,1,
            1,-1,-1,  0,-1,0, 0,1,
            1,-1, 1,  0,-1,0, 0,0,
           -1,-1, 1,  0,-1,0, 1,0,
    };

    std::vector<unsigned int> i;

    for (int f = 0; f < 6; ++f)
    {
        unsigned int o = f * 4;
        i.insert(i.end(), {
            o, o + 1, o + 2,
            o + 2, o + 3, o
            });
    }

    return Geometry(v, i, 8);
}

Geometry Geometry::Sphere(int segments, int rings)
{
    std::vector<float> v;
    std::vector<unsigned int> i;

    for (int y = 0; y <= rings; ++y)
    {
        float vCoord = (float)y / rings;
        float phi = vCoord * M_PI;

        for (int x = 0; x <= segments; ++x)
        {
            float uCoord = (float)x / segments;
            float theta = uCoord * 2.0f * M_PI;

            float xPos = sin(phi) * cos(theta);
            float yPos = cos(phi);
            float zPos = sin(phi) * sin(theta);

            // position
            v.push_back(xPos);
            v.push_back(yPos);
            v.push_back(zPos);

            // normal (same as position normalized)
            v.push_back(xPos);
            v.push_back(yPos);
            v.push_back(zPos);

            // uv
            v.push_back(uCoord);
            v.push_back(vCoord);
        }
    }

    for (int y = 0; y < rings; ++y)
    {
        for (int x = 0; x < segments; ++x)
        {
            unsigned int i0 = y * (segments + 1) + x;
            unsigned int i1 = i0 + segments + 1;

            i.insert(i.end(), {
                i0, i1, i0 + 1,
                i1, i1 + 1, i0 + 1
                });
        }
    }

    return Geometry(v, i, 8);
}

Geometry Geometry::Capsule(float radius, float height, int segments, int rings) //broken
{
    std::vector<float> v;
    std::vector<unsigned int> i;

    float halfHeight = height * 0.5f;

    int rows = 0;

    auto addRing = [&](float yPos, float r, float ny)
        {
            for (int x = 0; x <= segments; ++x)
            {
                float u = (float)x / segments;
                float theta = u * 2.0f * M_PI;

                float nx = cos(theta) * r;
                float nz = sin(theta) * r;

                v.push_back(nx * radius);
                v.push_back(yPos);
                v.push_back(nz * radius);

                v.push_back(nx);
                v.push_back(ny);
                v.push_back(nz);

                v.push_back(u);
                v.push_back((float)rows); // temp v, fix later
            }
            rows++;
        };

    // ?? Bottom hemisphere
    for (int y = 0; y <= rings; ++y)
    {
        float t = (float)y / rings;
        float phi = t * (M_PI / 2.0f);

        float ny = -cos(phi);
        float r = sin(phi);
        float yPos = -halfHeight + ny * radius;

        addRing(yPos, r, ny);
    }

    // ?? Cylinder (IMPORTANT: multiple rings!)
    int cylinderRings = rings;

    for (int y = 1; y < cylinderRings; ++y)
    {
        float t = (float)y / cylinderRings;
        float yPos = -halfHeight + t * height;

        addRing(yPos, 1.0f, 0.0f);
    }

    // ?? Top hemisphere
    for (int y = 0; y <= rings; ++y)
    {
        float t = (float)y / rings;
        float phi = t * (M_PI / 2.0f);

        float ny = cos(phi);
        float r = sin(phi);
        float yPos = halfHeight + ny * radius;

        addRing(yPos, r, ny);
    }

    int totalRows = rows;

    // ?? Indices
    for (int y = 0; y < totalRows - 1; ++y)
    {
        for (int x = 0; x < segments; ++x)
        {
            unsigned int i0 = y * (segments + 1) + x;
            unsigned int i1 = i0 + segments + 1;

            i.insert(i.end(), {
                i0, i1, i0 + 1,
                i1, i1 + 1, i0 + 1
                });
        }
    }

    // ? Fix UV V coordinate
    int vertsPerRow = segments + 1;
    for (int y = 0; y < totalRows; ++y)
    {
        float vCoord = (float)y / (totalRows - 1);
        for (int x = 0; x <= segments; ++x)
        {
            int idx = (y * vertsPerRow + x) * 8 + 7;
            v[idx] = vCoord;
        }
    }

    return Geometry(v, i, 8);
}