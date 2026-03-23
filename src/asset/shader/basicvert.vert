//#version 330 core
//
//layout (location = 0) in vec3 aPos;
////layout (location = 1) in vec2 aUV;
//
////out vec2 vUV;
//
//uniform mat4 uMVP;
//
//void main()
//{
//  //  vUV = aUV;
//    gl_Position = uMVP * vec4(aPos, 1.0);
//}

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

// Fullscreen triangle using gl_VertexID (no vertex attributes needed)
const vec2 verts[3] = vec2[](
    vec2(-1.0, -1.0),
    vec2( 3.0, -1.0),
    vec2(-1.0,  3.0)
);
out vec2 vUV;
out vec3 vNormal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = projection * view * model * vec4(aPos,1.);//vec4(verts[gl_VertexID], 0.0, 1.0);
   // gl_Position = vec4(verts[gl_VertexID], 0.0, 1.0); 
    vUV = aUV; // Convert from [-1, 1] to [0, 1]
    vNormal = aNormal;
}