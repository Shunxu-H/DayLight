#version 130
attribute vec3 vert;
uniform vec3 color;
uniform mat4 ModelViewProjectionMatrix;

out vec3 fragColor;

void main(void)
{
    fragColor = color;
    gl_Position = ModelViewProjectionMatrix * vec4(vert, 1.0f);
}
