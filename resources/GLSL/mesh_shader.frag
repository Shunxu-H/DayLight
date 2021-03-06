#version 130

uniform mat4 model;
uniform mat4 inverseModel;
uniform vec3 ambient;

uniform struct Light {
   vec3 position;
   vec3 intensities; //a.k.a the color of the light
} light;

in vec3 fragNormal;
in vec3 fragVert;

out vec4 finalColor;



void main() {
    //calculate normal in world coordinates
    mat4 normalMatrix = transpose(inverseModel);
    vec3 normal = normalize( (normalMatrix * vec4( fragNormal, 1 )).xyz );

    //calculate the location of this fragment (pixel) in world coordinates
    vec3 fragPosition = (model * vec4(fragVert, 1)).xyz;

    //calculate the vector from this pixels surface to the light source
    vec3 surfaceToLight = light.position - fragPosition;

    //calculate the cosine of the angle of incidence
    float brightness = dot(normal, surfaceToLight) / (length(surfaceToLight) * length(normal));
    brightness = clamp(brightness, 0, 1);

    //calculate final color of the pixel, based on:
    // 1. The angle of incidence: brightness
    // 2. The color/intensities of the light: light.intensities
    // 3. The texture and texture coord: texture(tex, fragTexCoord)
    vec4 surfaceColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    finalColor = vec4(brightness * light.intensities * surfaceColor.rgb + ambient, surfaceColor.a);
}
