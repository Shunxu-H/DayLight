#version 150

uniform mat4 camera;
uniform mat4 model;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix; 

in vec3 aPos;
in vec3 aNormal;
in vec2 aTexCoords;


out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} vs_out;

void main() {
    vs_out.FragPos = vec3(model * vec4(aPos, 1.0));
    vs_out.Normal = transpose(inverse(mat3(model))) * aNormal;
    vs_out.TexCoords = aTexCoords;
    vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
    gl_Position = projection * camera * model * vec4(aPos, 1.0);

}
