#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 crtPos;
uniform mat4 camMatrix;
uniform mat4 model;


void main()
{
    TexCoords = aTexCoords;
    gl_Position = camMatrix * model* vec4(aPos,1.0);
    crtPos = vec3(model* vec4(aPos,1.0f));
    Normal = aNormal;
}