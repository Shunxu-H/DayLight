#version 130

uniform mat4 projection;
uniform mat4 camera;
//uniform mat4 model;

in vec4 vert;
//in vec2 vertTexCoord;

//out vec2 fragTexCoord;

void main() {
    // Pass the tex coord straight through to the fragment shader
    //fragTexCoord = vertTexCoord;

    // Apply all matrix transformations to vert
    gl_Position = projection * camera * vert;
}
