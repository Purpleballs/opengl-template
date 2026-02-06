#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 wpos;
out vec3 lspace;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
    wpos = (model * vec4(aPos,1.)).xyz;
    lspace = aPos;

    //vec3 test = vec3(1);
   // wpos = (model * vec4(test,1.)).xyz;
}