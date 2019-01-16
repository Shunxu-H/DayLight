#pragma once 

#include <Patronus/DirectionalLight.h>
#include <Patronus/PointLight.h>

namespace Daylight{
    namespace Patronus{
        class LightFactory{        
        public:
            static DirectionalLight * makeDirectionalLight(
                const point3 & position = glm::vec3(1, 0.8, 0.6), //w == 0 indications a directional light
                const point3 & intensity = glm::vec3(1.0,1.0,1.0), //weak yellowish light
                const float & ambientCoefficient = 0.06f
                ); 
            
            static PointLight * makePointLight(
                const point3 & position = glm::vec3(-4,0,10),
                const color3 & intensity = glm::vec3(2.0,2.0,2.0), //strong white light
                const float & attenuation = 0.1f,
                const float & ambientCoefficient = 0.0f, //no ambient light
                const float & coneAngle = 15.0f,
                const glm::vec3 & coneDirection = glm::vec3(0,0,-1)
                );
        }; 
    }
}