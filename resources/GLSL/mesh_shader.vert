#version 130


uniform mat4 camera;
uniform mat4 model;
uniform mat4 projection;

in vec3 aPos;
in vec3 aNormal;

out vec3 fragVert;
out vec3 fragNormal;

void main() {
    // Pass some variables to the fragment shader
    fragNormal = aNormal;
    fragVert = aPos;

    // Apply all matrix transformations to vert
    gl_Position = projection * camera * model * vec4(aPos, 1.0f);
}
