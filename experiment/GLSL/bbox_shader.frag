#version 130
varying vec4 qt_TexCoord0;

in vec3 fragColor;

void main(void)
{
    gl_FragColor = vec4(fragColor, 1.0f);
}
