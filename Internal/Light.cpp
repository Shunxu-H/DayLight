#include "GL_include.h"
#include "Light.h"

namespace Patronus {


Light Light::makeDirectionalLight(const point3 & position, const point3 & intensity, const float & ambientCoefficient){
    Light directionalLight(position);
    directionalLight._type = LightType::DIRECTIONAL;
    directionalLight._intensity = intensity; //weak yellowish light
    directionalLight._ambientCoefficient = ambientCoefficient;
    return directionalLight;
}

Light Light::makePointLight( const point3 & position,
                      const color3 & intensity,
                      const float & attenuation,
                      const float & ambientCoeffient,
                      const float & coneAngle,
                      const glm::vec3 & coneDirection){
    Light spotlight(position);
    spotlight._type = LightType::SPOT;
    spotlight._intensity = intensity; //strong white light
    spotlight._attenuation = attenuation;
    spotlight._ambientCoefficient = ambientCoeffient; //no ambient light
    spotlight._coneAngle = coneAngle;
    spotlight._coneDirection = coneDirection;
    return spotlight;
}



}
