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
                const float      & fov   = glm::radians(60.0f),
                const float      & near  = 0.1f,
                const float      & far   = 1000.0f,
                const point3     & pos   = glm::vec3(  0,  2,  5 ),
                const glm::vec3  & up    = glm::vec3(  0,  1,  0 ),
                const glm::vec3  & at    = glm::vec3(  0,  0, -1 )

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


        void moveForward( const float & dist );
        void panAndPadestal( const float & x_axis, const float & y_axis );
        void rotateAroundFocus( const float & x_axis, const float & y_axis);
        glm::mat4 getPerspectiveMatrix()const;
        glm::mat4 getProjectionMatrix(const float & aspect_ratio )const;


        void loadUniforms( const unsigned int & width, const unsigned int & height ) const;
        void getColorAndDepthTexture(const unsigned int & width,
                                     const unsigned int & height,
                                     GLuint * colorTexture,
                                     GLuint * depthTexture )const;

        void genFrameBuffer( const unsigned int & width, const unsigned int & height );
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
