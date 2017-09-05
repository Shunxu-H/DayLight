#ifndef SHADER_H
	#define SHADER_H

#include <vector>
#include <string>
#include <memory>
#include "GL_include.h"
#include "GLObject.h"
#include "Countable.h"

namespace Lumos {

    class Shader : public GLObject, public Countable
    {
    public:
        Shader(){}
        virtual ~Shader();
        virtual void bind () const{}

        /**
         * @brief readFromFile, creat a shader from file
         * @param filePath, path to the shader file
         * @param shaderType,
         * @return the constructed shader
         */
        static Shader readFromFile(const std::string & filePath, const GLenum & shaderType );
        /**
         * @brief readFromFiles, construct a vector of shader using the shader files in @shaderDir
         * @param shaderDir, path to the directory where shader files are stored
         * @return a vector of shader
         */
        static std::vector<Shader> readFromFiles( const std::string & shaderDir );


    protected:


    private:
        /**
         * @brief Shader
         * @param filePath file path to the GLSL file
         * @param shaderType type of shader
         *        must be
         *        GL_COMPUTE_SHADER | GL_VERTEX_SHADER |
         *        GL_TESS_CONTROL_SHADER | GL_TESS_EVALUATION_SHADER |
         *        GL_Mesh_SHADER | GL_FRAGMENT_SHADER
         */
        Shader(const std::string & filePath, const GLenum & shaderType );

        void _glCleanUp();

        bool loadFile_obj(const std::string &);


    };

}

	#endif
