#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;


uniform mat4 camMatrix;
uniform mat4 model;
out vec3 Normal;
out vec3 vColor;
out vec2 vTexCoord;

void main()
{
    gl_Position = camMatrix * model* vec4(aPos,1.0);
    Normal = aNormal;
    vTexCoord = aTex;
    //vTexCoord = vec3(aPos.x, aPos.y, -aPos.z);
}