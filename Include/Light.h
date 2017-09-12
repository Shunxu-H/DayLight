#ifndef LIGHT_H
#define LIGHT_H

#include "GL_include.h"
#include "Transformable.h"

namespace Patronus {

    enum class LightType{
        DIRECTIONAL,
        SPOT,
        CONE
    };

    class Light: public Transformable
    {
    public:

        Light   (
                const point3 & position = point3 ( 0.0f, 5.0f, 0.0f ),
                const color3 & intensity = color3 ( 1.0f, 1.0f, 1.0f)
                )
                : Transformable( position ),
                _intensity( intensity ){}


        virtual ~Light() override{ }

        bool isOn() const { return _isOn; }

        static Light makeDirectionalLight(
                const point3 & position = glm::vec3(1, 0.8, 0.6), //w == 0 indications a directional light
                const point3 & intensity = glm::vec3(1.0,1.0,0.1), //weak yellowish light
                const float & ambientCoefficient = 0.06f
                );

        static Light makePointLight(
                const point3 & position = glm::vec3(-4,0,10),
                const color3 & intensity = glm::vec3(2.0,2.0,2.0), //strong white light
                const float & attenuation = 0.1f,
                const float & ambientCoefficient = 0.0f, //no ambient light
                const float & coneAngle = 15.0f,
                const glm::vec3 & coneDirection = glm::vec3(0,0,-1)
                );



        static Light makePointLight();



        /**
         * @brief setter and getter for private members
         */
        inline color3
            getIntensity() const { return _intensity; }
        inline void
            setIntensity( const color3 & _i ) { _intensity = _i; }

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

        inline float
            getConeAngle() const { return _coneAngle; }
        inline void
            setConeAngle( const float & angle ) { _coneAngle = angle; }

        inline glm::vec3
            getConeDirection() const { return _coneDirection; }
        inline void
            setConeDirection( const glm::vec3 & direction ) { _coneDirection = direction; }

        inline LightType
            getType() const { return _type; }
        inline void
            setType( const LightType & type) { _type = type; }


    protected:

    private:
        LightType _type;
        color3 _intensity;
        float _attenuation;
        float _ambientCoefficient;
        float _coneAngle;
        glm::vec3 _coneDirection;
        bool _isOn;

    };
}

#endif // LIGHT_H
