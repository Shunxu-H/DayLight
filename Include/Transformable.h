#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include "GL_include.h"

namespace Patronus {

    class Transformable{
    public:
        Transformable(const point3 & pos = point3 (0.0f, 0.0f, 0.0f)):
            _translate      ( pos ),
            _scale          ( point3 (1.0f, 1.0f, 1.0f)),
            _orientation    ( point3 (0.0f, 0.0f, 0.0f)){}
        virtual ~Transformable(){}


        virtual void translate ( const float & x, const float & y, const float & z );
        virtual void scale ( const float & x, const float & y, const float & z );
        virtual void rotate ( const float & x, const float & y, const float & z );

        /**
         * @brief getModalMatrix,
         *          use internal data ( _translation, _scale, _orientation ) to calculate modal matrix
         */
        virtual glm::mat4 getModelMatrix() const;

        virtual glm::mat4 getInverseModelMatrix() const;

        //virtual void operator*( const glm::mat4 & m ) = 0;

        /**
         * @brief setter and getter for private members
         */
        inline point3
            getTranslate() const { return _translate; }
        inline point4
            getTranslatev4() const { return point4(_translate, 1.0f); }
        inline point3
            getScale() const { return _scale; }
        inline point3
            getOrientation() const { return _orientation; }

        inline void
            setTranslate( const point3 & arg ) { _translate=arg; }
        inline void
            setTranslatev4( const point4 & arg){ _translate = glm::vec3(arg); }
        inline void
            setScale( const point3 & arg ) { _scale=arg; }
        inline void
            setOrientation( const point3 & arg ) { _orientation=arg; }

    protected:
        point3 _translate;
        point3 _scale;
        point3 _orientation;


    private:

};
}

#endif // TRANSFORMABLE_H
