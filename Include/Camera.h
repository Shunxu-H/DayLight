#ifndef CAMERA_H
#define CAMERA_H

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
        Camera(

                const CameraType & type  = CameraType::PERSPECTIVE,
                const float      & fov   = glm::radians(60.0f),
                const float      & near  = 0.5f,
                const float      & far   = 100000.0f,
                const point3     & pos   = glm::vec3(  0,  2,  5 ),
                const glm::vec3  & up    = glm::vec3(  0,  1,  0 ),
                const glm::vec3  & at    = glm::vec3(  0,  0, -1 )

               );

        virtual ~Camera(){}

        static Camera* pers;

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


        //virtual void operator*( const glm::mat4 & m );

        void moveForward( const float & dist );
        void panAndPadestal( const float & x_axis, const float & y_axis );
        void rotateAroundFocus( const float & x_axis, const float & y_axis);
        glm::mat4 getPerspectiveMatrix()const;
        glm::mat4 getProjectionMatrix(const float & aspect_ratio )const;
    protected:

    private:
        CameraType _type;
        glm::vec3 _up;
        glm::vec3 _at;
        float _fov;
        float _near;
        float _far;

    };

}

#endif // CAMERA_H
