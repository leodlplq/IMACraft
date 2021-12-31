#version 330 core

layout(location = 3) in vec2 aVertexPosition;
layout(location = 4) in vec2 aVertexTexCoords;

out vec2 vFragTexCoords;
uniform mat4 modelHP;


void main() {
    gl_Position = modelHP * vec4(aVertexPosition*0.15, 0, 1);
    vFragTexCoords = aVertexTexCoords;
}