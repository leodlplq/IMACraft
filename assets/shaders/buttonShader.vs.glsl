#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

uniform mat4 projection;

out vec3 vColor;
void main()
{
    gl_Position = projection * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    //gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vColor = aColor;
}
