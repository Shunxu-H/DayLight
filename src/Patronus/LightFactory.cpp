#include <Patronus/LightFactory.h>

using namespace Daylight; 
using namespace Daylight::Patronus; 

DirectionalLight * LightFactory::makeDirectionalLight(
                const point3 & position, //w == 0 indications a directional light
                const point3 & intensity, //weak yellowish light
                const float & ambientCoefficient
                )
{
    DirectionalLight * dl = new DirectionalLight{}; 
    dl->setTranslate(position); 
    dl->setIntensity(intensity); 
    dl->setAmbientCoefficient(ambientCoefficient); 
    return dl; 
}


PointLight * LightFactory::makePointLight(
    const point3 & position,
    const color3 & intensity, //strong white light
    const float & attenuation,
    const float & ambientCoefficient, //no ambient light
    const float & coneAngle,
    const glm::vec3 & coneDirection
    )
{
    PointLight * pl = new PointLight(); 
    pl->setTranslate(position); 
    pl->setIntensity(intensity); 
    pl->setAttenuation(attenuation); 
    pl->setAmbientCoefficient(ambientCoefficient);
    pl->setConeAngle(coneAngle);
    pl->setConeDirection(coneDirection); 
    return pl; 
}