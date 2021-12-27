#version 330 core

in vec3 vColor;
in vec3 vTexCoord;

uniform sampler2D texture_diffuse2;

out vec4 FragColor;

void main()
{
   FragColor = texture(texture_diffuse2,vTexCoord);
   //FragColor = vec4(vColor,1.0);
}