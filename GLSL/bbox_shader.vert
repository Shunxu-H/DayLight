attribute vec3 vert;

uniform mat4 ModelViewProjectionMatrix;

void main(void)
{
    gl_Position = ModelViewProjectionMatrix * vec4(vert, 1.0f);
}
