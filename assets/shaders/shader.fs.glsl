#version 330 core

in vec3 Normal;
in vec2 vTexCoord;

uniform sampler2D texture_diffuse1;

out vec4 FragColor;

void main()
{
   FragColor = texture(texture_diffuse1,vTexCoord);
   //FragColor = vec4(1.0,0,0,1.0);
}