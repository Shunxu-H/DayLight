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
#ifndef PROGRAM_H
#define PROGRAM_H

#include <GL/gl.h>
#include <unordered_map>
#include <vector>
#include <sstream>
#include "Common/GL_include.h"
#include "GLObject.h"

#include "Shader.h"

#include "ArrayBuffer.h"

/**
 * @TODO:
 * 1. Enable more than two shaders in pipes
 */

namespace Patronus {
    class PhysicalWorld; 
    class Shaper; 
}

namespace Lumos {
    using shading_pipe = std::vector<Shader>;

    /**
     * @brief manages a list of drawing instances, interface between openGL and the rest of the program
     *
     */
    class Program: public GLObject{
    public:
        Program();
        /**
         * @brief should only called this constructor
         * @param shaders a vector of Shader to be kinked to this program
         */
        // Program(std::vector<Shader> shaders);

        /**
         * @brief loadShaders, load a list of shaders from a directory
         * @param GLSL_path, the path to a directory containing the shader files
         */
        void loadShaders(const std::string & GLSL_path);

        ~Program();

        /**
         * [enableShadingPipe enable a shading pipe]
         * @param pipe_name [name of the shading pipe]
         * Note: shading pipe is a collection of Lumos::Shader that construct
         * a complete openGL workflow
         */
        void enableShadingPipe( const std::string & pipe_name );
        /**
         * [disableShadingPipe disable a shading pipe]
         * @param pipe_name [name of the shading pipe to disable]
         */
        void disableShadingPipe( const std::string & pipe_name );

        /**
         * @brief getAttrib: get the OpenGL handler based on the attribName
         * @param attribName: should match what we have in the shader files
         * @return the openGL attrib handler for the name specified
         */
        GLint getAttrib(const GLchar* attribName) const;

        /**
         * @brief getUniform: get the OpenGL handler for uniform variable based on the attribName
         * @param uniformName: should match what we have in the shader files
         * @return the openGL attrib handler for the name specified
         */
        GLint getUniform(const GLchar* uniformName) const;
        // disable copy constructor
        Program(const Program&)=delete;
        /**
         * @brief wrapper class to provide access to OpenGL
         */
        void use() const override;
        bool isInUse() const override;
        void stopUsing() const override;
        void bind() const;


        void preDrawSetUp( );

        /**
          * Credit to Tom Dalling
          * @ http://tomdalling.com/blog/modern-opengl/01-getting-started-in-xcode-and-visual-cpp/
          *
          **/
        #define _TDOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(OGL_TYPE) \
        void setAttrib(const GLchar* attribName, OGL_TYPE v0); \
        void setAttrib(const GLchar* attribName, OGL_TYPE v0, OGL_TYPE v1); \
        void setAttrib(const GLchar* attribName, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2); \
        void setAttrib(const GLchar* attribName, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3); \
\
        void setAttrib1v(const GLchar* attribName, const OGL_TYPE* v); \
        void setAttrib2v(const GLchar* attribName, const OGL_TYPE* v); \
        void setAttrib3v(const GLchar* attribName, const OGL_TYPE* v); \
        void setAttrib4v(const GLchar* attribName, const OGL_TYPE* v); \
\
        void setUniform(const GLchar* uniformName, OGL_TYPE v0); \
        void setUniform(const GLchar* uniformName, OGL_TYPE v0, OGL_TYPE v1); \
        void setUniform(const GLchar* uniformName, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2); \
        void setUniform(const GLchar* uniformName, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3); \
\
        void setUniform1v(const GLchar* uniformName, const OGL_TYPE* v, GLsizei count=1); \
        void setUniform2v(const GLchar* uniformName, const OGL_TYPE* v, GLsizei count=1); \
        void setUniform3v(const GLchar* uniformName, const OGL_TYPE* v, GLsizei count=1); \
        void setUniform4v(const GLchar* uniformName, const OGL_TYPE* v, GLsizei count=1); \

        _TDOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(GLfloat)
        _TDOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(GLdouble)
        _TDOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(GLint)
        _TDOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(GLuint)


        void setUniformMatrix2(const GLchar* uniformName, const GLfloat* v, GLsizei count=1, GLboolean transpose=GL_FALSE);
        void setUniformMatrix3(const GLchar* uniformName, const GLfloat* v, GLsizei count=1, GLboolean transpose=GL_FALSE);
        void setUniformMatrix4(const GLchar* uniformName, const GLfloat* v, GLsizei count=1, GLboolean transpose=GL_FALSE);
        void setUniform(const GLchar* uniformName, const glm::mat2& m, GLboolean transpose=GL_FALSE);
        void setUniform(const GLchar* uniformName, const glm::mat3& m, GLboolean transpose=GL_FALSE);
        void setUniform(const GLchar* uniformName, const glm::mat4& m, GLboolean transpose=GL_FALSE);
        void setUniform(const GLchar* uniformName, const glm::vec3& v);
        void setUniform(const GLchar* uniformName, const glm::vec4& v);

        /**
         * [hasAttribute check if the shader pipe attached to this program has
         *      a atrribute]
         * @param  attribName [name to be check]
         */
        bool hasAttribute( const GLchar * attribName ) const;
        /**
         * [hasUniform check if the shader pipe attached to this program has
         *      a uniform]
         * @param  attribName [description]
         * @return            [description]
         */
        bool hasUniform( const GLchar * uniformName ) const;

        /**
         * [SetLightUniform to more than 1 lights]
         * @param propertyName [description]
         * @param lightIndex   [description]
         * @param value        [description]
         */
        template <typename T>
        void SetLightUniform(const char* propertyName, size_t lightIndex, const T& value) {
            std::ostringstream ss;
            ss << "allLights[" << lightIndex << "]." << propertyName;
            std::string uniformName = ss.str();

            setUniform(uniformName.c_str(), value);
        }

    private:


        std::unordered_map<std::string, shading_pipe> _shading_pipes;


    };
}


#endif // PROGRAM_H
