/*
The MIT License (MIT)

Copyright (c) 2016-2018, Shunxu Huang, shunxuhuang@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include "Common/GL_include.h"
/**
 * Transformable
 * EVerything that can be moved in the scene will be inheriting from this class
 */
namespace Daylight::Patronus {
    class Transformable{
    public:
        Transformable(const point3 & pos = point3 (0.0f, 0.0f, 0.0f)):
            _translate      ( pos ),
            _scale          ( point3 (1.0f, 1.0f, 1.0f)),
            _orientation    ( point3 (0.0f, 0.0f, 0.0f)),
            _isOn           (true){}
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

        bool isOn() const { return _isOn; }
        inline void
            turnOn() { _isOn = true; }
        inline void
            turnOff() { _isOn = false; }


    protected:
        point3 _translate;
        point3 _scale;
        point3 _orientation;
        bool _isOn;


    private:

};
}

#endif // TRANSFORMABLE_H
