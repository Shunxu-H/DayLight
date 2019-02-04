#pragma once 

#include <Patronus/ILight.h>
#include <Lumos/Program.h>

namespace Daylight{
    namespace Patronus {
        class DirectionalLight : public ILight{
        public:
            void setUniformsAndAttributes(Lumos::Program program, void* data) override;

            unsigned int getLightType()const override { return LIGHT_DIRECTIONAL; }

            glm::mat4 getLightSpaceMatrix() const; 
            
            // getter and setter
            inline float getAngle() const {return _angle;}
            inline void setAngle(const float & angle) {_angle = angle; }

        protected:

        private:
            float _angle; 

        }; 
    }
}