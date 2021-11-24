#version 330 core

in vec3 vColor;
in vec3 vTexCoord;

uniform samplerCube tex0;

out vec4 FragColor;

void main()
{
   FragColor = texture(tex0,vTexCoord);
   //FragColor = vec4(vColor,1.0);
}