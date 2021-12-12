#version 330 core

in vec3 vColor;
in vec3 vTexCoord;


out vec4 FragColor;

void main()
{
   //FragColor = texture(tex0,vTexCoord);
   FragColor = vec4(vec3(0.1,0.2,0.6),1.0);
}