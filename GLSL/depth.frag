#version 130

out vec4 outColor;

//layout ( locationi = 1) out float depth;


void main(void)
{
    float z = gl_FragCoord.z;
    //depth = gl_FragCoord.z;
    outColor = vec4( z, z, z, 1);
}
