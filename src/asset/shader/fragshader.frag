#version 460 core

#define MAX_STEPS 50

#define HIT_DIST 0.001
out vec4 FragColor;

in vec2 TexCoord;
in vec3 wpos;
in vec3 lspace;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec2 res;
uniform mat4 rot;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 cpos;

uniform mat4 views;

float scene(vec3 p)
{
  //  p = fract(p-.5)-.5;
   // return length(vec2(length(p.xz)-.3,p.y))-.1;
    return length(max(vec3(0),abs(p)-.25))-.1;
}

float rayMarch(vec3 ro,vec3 rd)
{
    float dist = 0.;
    for(int i = 0; i< MAX_STEPS;i++)
    {      
       float dcp =  scene(ro + rd*dist);
       dist  += dcp;
       if(dcp<HIT_DIST ) break;  //|| dist > sqrt(3)  diagonal unit cube
    }
    return dist;
}
void main()
{
    
    vec3 ro = lspace;
         //ro = cpos;
    vec3 wrd = normalize(wpos-cpos);
    vec3 lrd = vec3(inverse(model) * vec4(wrd,0.));
    float dist = rayMarch(ro,lrd) ;
    vec3 p = ro + lrd*dist;
    if(scene(p)  > 0.1) discard;
    vec3 col = vec3(226, 114, 91)/255.;

    vec3 norm = normalize(vec3(
        scene(p+vec3(HIT_DIST,0,0))-scene(p-vec3(HIT_DIST,0,0)),
        scene(p+vec3(0,HIT_DIST,0))-scene(p-vec3(0,HIT_DIST,0)),
        scene(p+vec3(0,0,HIT_DIST))-scene(p-vec3(0,0,HIT_DIST))
    )); 


    //word space from here
    p = wpos + wrd * dist;
    p.z = -p.z;
        norm = normalize((model*vec4(norm,0.)).xyz);
        norm.z = -norm.z;
    vec3 lpos = vec3(0,0,.5);
    vec3 ldir = normalize(lpos - p);

    float dif = clamp(dot(norm,ldir),0.,1.);
    FragColor = vec4( dif*col,1.);

}