#ifndef SHAPER_H
#define SHAPER_H

#include <vector>
#include <string>
#include <memory>
#include "GL_include.h"
#include "Camera.h"
#include "Geometry.h"
#include "ArrayBuffer.h"

namespace Patronus {
    class Shaper{
    public:
        Shaper():_pers( std::make_shared<Camera, CameraType> (CameraType::PERSPECTIVE ) ) { }

        Shaper( const std::string & fileName );

        inline

        /**
         * @brief load file and call corresponding functions based on file extension
         * @param fileName the file targeted to be loaded
         * @return boolean if the file is successfully loaded
         */
        bool loadFile( const std::string & fileName );

        inline bool
            isLoaded() const { return _shapes.size() > 0; }

        inline std::shared_ptr<Camera>
            getPerspectiveCam() const { return _pers; }

        int getNumOfVertices() const;

        Lumos::ArrayBuffer getBuffer()const;


    protected:

    private:
        std::vector<Geometry> _shapes;
        std::vector<Camera> _cameras;
        std::shared_ptr<Camera> _pers;

        bool _loadFile_obj(const std::string & f_name);

    };

}

#endif // SHAPER_H
