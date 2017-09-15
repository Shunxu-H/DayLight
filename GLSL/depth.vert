#version 130

uniform mat4 camera;
uniform mat4 model;
uniform mat4 projection;

in vec3 vert;



void main() {
    // Pass some variables to the fragment shader
    // fragTexCoord = vertTexCoord;

    // Apply all matrix transformations to vert
    gl_Position =  projection * camera * model * vec4(vert, 1);

}
