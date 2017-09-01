#ifndef SHAPER_H
#define SHAPER_H

#include <vector>
#include <string>
#include <memory>
#include "GL_include.h"
#include "Geometry.h"

namespace Patronus {
    class Shaper{
    public:
        Shaper( const std::string & fileName );

        /**
         * @brief load file and call corresponding functions based on file extension
         * @param fileName the file targeted to be loaded
         * @return boolean if the file is successfully loaded
         */
        bool loadFile( const std::string & fileName );

        inline bool
            isLoaded() const { return _shapes.size() > 0; }

        GLuint getBuffer()const;

    protected:

    private:
        std::vector<Geometry> _shapes;

        bool _loadFile_obj(const std::string & f_name);

    };

}

#endif // SHAPER_H
