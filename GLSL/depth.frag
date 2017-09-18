#version 130

uniform float maxDepth;
out vec4 depth;


void main(void)
{
    float z = gl_FragCoord.z / gl_FragCoord.w;
    depth = vec4( z, z, z, 1);
}
