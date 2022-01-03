#version 330 core

out vec4 fFragColor;

in vec3 vFragColor;
in vec2 vFragTexCoords;

uniform sampler2D uTexture;

void main() {
    fFragColor = texture(uTexture, vFragTexCoords);
}