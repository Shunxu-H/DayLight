#version 150
uniform vec3 transmittance;
uniform bool hasTexture;
uniform sampler2D tex; //this is the texture

uniform mat4 model;
uniform mat4 inverseModel;
uniform vec3 cameraPosition;

uniform float materialShininess;
uniform vec3 materialSpecularColor;
uniform vec4 diffuseColor;
uniform sampler2D shadowMap;

#define MAX_LIGHTS 10
uniform int numLights;
uniform struct Light {
   bool isDirectional;
   vec4 position;
   vec3 intensities; //a.k.a the color of the light
   float attenuation;
   float ambientCoefficient;
   float coneAngle;
   vec3 coneDirection;
} allLights[MAX_LIGHTS];

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

out vec4 outColor;
//layout (location = 1) out vec4 outTexture;

//layout(location = 0)out vec4 glFragData;


float ShadowCalculation(vec4 fragPosLightSpace)
{
        // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;

    return shadow;
}

vec3 ApplyLight(Light light, vec3 surfaceColor, vec3 normal, vec3 surfacePos, vec3 surfaceToCamera) {
    vec3 surfaceToLight;
    float attenuation = 1.0;
    if(light.isDirectional) {
        //directional light
        surfaceToLight = normalize(light.position.xyz);
        attenuation = 1.0; //no attenuation for directional lights
    } else {
        //point light
        surfaceToLight = normalize(light.position.xyz - surfacePos);
        float distanceToLight = length(light.position.xyz - surfacePos);
        attenuation = 1.0 / (1.0 + light.attenuation * pow(distanceToLight, 2));

        //cone restrictions (affects attenuation)
        float lightToSurfaceAngle = degrees(acos(dot(-surfaceToLight, normalize(light.coneDirection))));
        if(lightToSurfaceAngle > light.coneAngle){
            attenuation = 0.0;
        }
    }

    //ambient
    vec3 ambient = light.ambientCoefficient * surfaceColor.rgb * light.intensities * 0.5; 

    //diffuse
    float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));
    vec3 diffuse = diffuseCoefficient * surfaceColor.rgb * light.intensities;

    //specular
    float specularCoefficient = 0.0;
    if(diffuseCoefficient > 0.0)
        specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, normal))), materialShininess);
    vec3 specular = specularCoefficient * materialSpecularColor * light.intensities;

    //linear color (color before gamma correction)
    
    float shadow = ShadowCalculation(fs_in.FragPosLightSpace); 
    return ambient + ((1.0 - shadow)*attenuation*(diffuse + specular));
}


void main() {
    vec3 normal = normalize(transpose(mat3(inverseModel)) * fs_in.Normal);
    vec3 surfacePos = vec3(model * vec4(fs_in.FragPos, 1));
    vec4 surfaceColor;
    if (hasTexture){
        surfaceColor = texture(tex, fs_in.TexCoords);
    }
    else
        surfaceColor = diffuseColor;
    
    vec3 surfaceToCamera = normalize(cameraPosition - surfacePos);

    //combine color from all the lights
    vec3 linearColor = vec3(0);
    for(int i = 0; i < numLights; ++i){
        linearColor += ApplyLight(allLights[i], surfaceColor.rgb, normal, surfacePos, surfaceToCamera);
    }

    //final color (after gamma correction)
    vec3 gamma = vec3(1.0/2.2);
    outColor = vec4(pow(linearColor, gamma)*(1-transmittance) , surfaceColor.a);
    //outColor = outTexture;
    //glFragData = gl_FragColor;
    //colorToTexture = finalColor.xyz;
}
