#version 330 core
layout (location = 0) in vec3 vert;

uniform mat4 lightSpaceMatrix;
uniform mat4 model;

void main()
{
    gl_Position = lightSpaceMatrix * model * vec4(vert, 1.0);
}  