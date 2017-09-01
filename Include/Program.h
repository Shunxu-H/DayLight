#ifndef PROGRAM_H
#define PROGRAM_H

#include <GL/gl.h>
#include <vector>
#include "GLObject.h"
#include "Shader.h"

namespace Lumos {
    /**
     * @brief manages a list of shader, interface between openGL and the rest of the program
     *
     */
    class Program: public GLObject{
    public:
        Program(){ }
        /**
         * @brief should only called this constructor
         * @param shaders a vector of Shader to be kinked to this program
         */
        Program(std::vector<Shader> & shaders);
        ~Program();

        /**
         * @brief wrapper class to provide access to OpenGL
         */
        void use() const;

        bool isInUse() const;

        void stopUsing() const;

        /**
         * @brief getAttrib: get the OpenGL handler based on the attribName
         * @param attribName: should match what we have in the shader files
         * @return the openGL attrib handler for the name specified
         */
        GLint getAttrib(const GLchar* attribName) const;

        // disable copy constructor
        Program(const Program&)=delete;
    private:

    };
}


#endif // PROGRAM_H
