#version 150

uniform mat4 camera;
uniform mat4 model;
uniform mat4 projection;

in vec3 aPos;
in vec3 aNormal;
in vec2 vertTexCoord;

out vec3 fragVert;
out vec2 fragTexCoord;
out vec3 fragNormal;
out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} vs_out;

void main() {
    // Pass some variables to the fragment shader
    // fragTexCoord = vertTexCoord;
    vs_out.TexCoords = vertTexCoord;
    vs_out.Normal = aNormal;
    vs_out.FragPos = aPos;

    // Apply all matrix transformations to vert
    gl_Position = projection * camera * model * vec4(aPos, 1);

}
