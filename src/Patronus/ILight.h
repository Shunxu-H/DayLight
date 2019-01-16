#pragma once 


#include <Common/GL_include.h>
#include <Patronus/Transformable.h>

#define LIGHT_DIRECTIONAL   0x00000001u
#define LIGHT_POINT         0x00000002u

namespace Daylight{
    namespace Patronus{
        class ILight: public Transformable{
        public:
            virtual void setUniformsAndAttributes(void* data)=0;
            virtual unsigned int getLightType() const = 0; 
             /**
             * @brief setter and getter for private members
             */
            inline color3
                getIntensity() const { return _intensity; }
            inline void
                setIntensity( const color3 & _i ) { _intensity = _i; }

            bool isOn() const { return _isOn; }
            inline void
                turnOn() { _isOn = true; }
            inline void
                turnOff() { _isOn = false; }

            inline float
                getAttenuation() const { return _attenuation; }
            inline void
                setAttenuation( const float & n ) { _attenuation = n; }

            inline float
                getAmbientCoefficient() const { return _ambientCoefficient; }
            inline void
                setAmbientCoefficient( const float & n ) { _ambientCoefficient = n; }
        protected:

        private:
            color3 _intensity;
            float _attenuation;
            float _ambientCoefficient;
            bool _isOn;
        }; 
    }
}