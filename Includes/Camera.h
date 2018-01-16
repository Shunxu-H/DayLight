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
#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include "GL_include.h"

#include "Transformable.h"

namespace Patronus {
    enum class CameraType
    {
        ORTHO_XY,
        ORTHO_ZY,
        ORTHO_XZ,
        CABINET,
        PERSPECTIVE,
        TEXTVIEW
    };


    class Camera: public Transformable{
    public:
        /**** STATIC FUNCTION OR MEMBER ***/
        static Camera* pers;
        /**
         * @brief loadCamerasFromDir, load camera from a directory which contains files of camera names and stats
         *          Must be called after the global shaper object is called because the constructed cameras will be stored there
         * @param dir, the directory containing the necessary file
         */
        static void loadCamerasFromDir( const std::string & dir );

        /**** STATIC FUNCTION OR MEMBER ***/

        Camera(
                const std::string& camId = "",
                const CameraType & type  = CameraType::PERSPECTIVE,
                const glm::vec3  & up    = glm::vec3(  0,  1,  0 ),
                const glm::vec3  & at    = glm::vec3(  0,  0, -1 ),
                const float      & fov   = glm::radians(60.0f),
                const float      & near  = 0.2f,
                const float      & far   = 70.0f,
                const point3     & pos   = glm::vec3(  0,  2,  5 )

               );



        virtual ~Camera();



        /**
         * @brief setter and getter for private variable
         */
        inline CameraType
            getType() const { return _type; }
        inline glm::vec3
            getUp() const { return _up; }
        inline glm::vec3
            getAt() const { return _at; }
        inline float
            getFovy() const { return _fov; }
        inline float
            getNearClipDist() const { return _near; }
        inline float
            getFarClipDist() const { return _far; }
        inline std::string
            getId() const { return _camId; }

        inline void
            setType(const CameraType & type ) { _type = type; }
        inline void
            setUp(const point3 & p) { _up= p; }
        inline void
            setAt(const point3 & p) { _at= p; }
        inline void
            setAtGlobal( const point3 & p ) { _at = p - _translate; }
        inline void
            setFov(const float & fov) { _fov = fov; }
        inline void
            setNearClipDist(const float & dist) { _near = dist; }
        inline void
            setFarClipDist(const float & dist) { _far = dist; }
        inline void
            setId( const std::string & id ) { _camId = id; }

        /**
         * Camera movement functions
         */
        void moveForward( const float & dist );
        void panAndPadestal( const float & x_axis, const float & y_axis );
        void rotateAroundFocus( const float & x_axis, const float & y_axis);

        /**
         * [getPerspectiveMatrix get perspective matrix for use in openGL/glm]
         * @return [perspecitve matrix]
         */
        glm::mat4 getPerspectiveMatrix()const;

        /**
         * [getProjectionMatrix get projection matrix for use in openGL/glm]
         * @param  aspect_ratio [aspect ratio of the viewport]
         * @return              [projection matrix]
         */
        glm::mat4 getProjectionMatrix(const float & aspect_ratio )const;

        /**
         * [loadUniforms load uniform to the GLSL files]
         * @param width  [width of the viewport]
         * @param height [height of the viewport]
         */
        void loadUniforms( const unsigned int & width, const unsigned int & height ) const;


    protected:

    private:
        std::string _camId;
        CameraType _type;
        glm::vec3 _up;
        glm::vec3 _at;
        float _fov;
        float _near;
        float _far;

    };

}

#endif // CAMERA_H
