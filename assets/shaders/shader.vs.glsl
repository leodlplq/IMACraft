#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

uniform float scale;

uniform mat4 camMatrix;
uniform mat4 model;

out vec3 vColor;
out vec2 vTexCoord;
void main()
{
    gl_Position = camMatrix * model* vec4(aPos,1.0);

    vColor = aColor;
    vTexCoord = aTex;
}