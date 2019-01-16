#pragma once 

#include <Patronus/ILight.h>

namespace Daylight{
    namespace Patronus {
        class PointLight : public ILight{
        public:
            void setUniformsAndAttributes(void * data=nullptr) override;


            unsigned int getLightType()const override { return LIGHT_POINT; }

            glm::mat4 getLightSpaceMatrix() const; 
            
            // getter and setter
            inline void setConeAngle(const float & coneAngle){ _coneAngle = coneAngle; }
            inline float getConeAngle() const { return _coneAngle; }

            inline void setConeDirection( const glm::vec3 & coneDirection) { _coneDirection = coneDirection; }
            inline glm::vec3 getConeDirection() const { return _coneDirection; }

        protected:

        private:
            float _coneAngle;
            glm::vec3 _coneDirection;
            
        }; 
    }
}