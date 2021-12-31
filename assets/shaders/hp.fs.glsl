#version 330 core

in vec2 vFragTexCoords;

out vec4 fFragTexCoords;

uniform sampler2D uTexture;

void main() {
    fFragTexCoords = texture(uTexture, vFragTexCoords);
}