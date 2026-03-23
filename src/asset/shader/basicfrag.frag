#version 330 core

in vec2 vUV;
in vec3 vNormal;
out vec4 FragColor;

void main()
{
    float l = length(vUV-.5);
    vec3 col = vec3(l);
    
    FragColor = vec4(vNormal, 1.);
    //FragColor = vec4(vUV,0., 1.);
}