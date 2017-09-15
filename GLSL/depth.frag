#version 130


void main(void)
{
    float z = clamp(gl_FragColor.z, -1.0, 1000);
    gl_FragColor =   vec4( z, z, z, 1);
}
