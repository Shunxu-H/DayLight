#ifndef PROGRAM_H
#define PROGRAM_H

#include <GL/gl.h>
#include <vector>
#include "GL_include.h"
#include "GLObject.h"
#include "ArrayBuffer.h"
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
        Program(std::vector<Shader> shaders);
        ~Program();

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
        void use() const;

        bool isInUse() const;

        void stopUsing() const;

        void bind() const;

        void attachAllShaders() const;
        void detachAllShaders() const;

        void preDrawSetUp();

        inline ArrayBuffer
            getCurVBO() const { return _curVBO; }
        inline GLuint
            getCurVAO() const { return _curVAO; }

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

    private:
        std::vector<Shader> _shaders;
        ArrayBuffer _curVBO;
        GLuint _curVAO;


    };
}


#endif // PROGRAM_H
