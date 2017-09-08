#version 130


uniform mat4 camera;
uniform mat4 model;
uniform mat4 projection;

in vec3 vert;
in vec3 vertNormal;

out vec3 fragVert;
out vec3 fragNormal;

void main() {
    // Pass some variables to the fragment shader
    fragNormal = vertNormal;
    fragVert = vert;

    // Apply all matrix transformations to vert
    gl_Position = projection * camera * model * vec4(vert, 1.0f);
}
