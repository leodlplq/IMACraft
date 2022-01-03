#version 330 core

layout(location = 3) in vec2 aVertexPosition;
layout(location = 4) in vec3 aVertexColor;
layout(location = 5) in vec2 aVertexTexCoords;

out vec3 vFragColor;
out vec2 vFragTexCoords;
uniform mat4 modelHP;
// uniform mat4 camMatrix;

void main() {
    gl_Position = modelHP * vec4(aVertexPosition, 0, 1);
    vFragColor = aVertexColor;
    vFragTexCoords = aVertexTexCoords;
}