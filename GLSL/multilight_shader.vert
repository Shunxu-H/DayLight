#version 330

uniform mat4 camera;
uniform mat4 model;
uniform mat4 projection;

in vec3 vert;
in vec3 vertNormal;
in vec2 vertTexCoord;

out vec3 fragVert;
out vec2 fragTexCoord;
out vec3 fragNormal;

void main() {
    // Pass some variables to the fragment shader
    // fragTexCoord = vertTexCoord;
    fragTexCoord = vertTexCoord;
    fragNormal = vertNormal;
    fragVert = vert;

    // Apply all matrix transformations to vert
    gl_Position = projection * camera * model * vec4(vert, 1);

}
