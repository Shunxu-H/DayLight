#ifndef LIGHT_H
#define LIGHT_H

#include "GL_include.h"
#include "Transformable.h"

namespace Patronus {
    struct GLSL_light{
        point3 position;
        color3 intensity;
        GLSL_light( const point3 & _p, const color3 & _i ): position( _p ),  intensity( _i ) {}
    };

    class Light: public Transformable
    {
    public:

        Light   (
                const color3 & intensity = color3 ( 1.0f, 1.0f, 1.0f),
                const point3 & position = point3 ( 0.0f, 5.0f, 0.0f )
                )
                : Transformable( position ),
                _intensity( intensity ){}


        virtual ~Light() override{ }

        bool isOn() const { return _isOn; }


        /**
         * @brief construct a GLSL struct to pass to OpenGL
         * @return a GLSL_light
         */
        inline GLSL_light
            getStruct () const { return GLSL_light ( _translate, _intensity ); }

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
    protected:

    private:
        color3 _intensity;
        bool _isOn;

    };
}

#endif // LIGHT_H
