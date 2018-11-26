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
#ifndef SHADER_H
	#define SHADER_H

#include <vector>
#include <string>
#include <memory>
#include "Common/GL_include.h"
#include "GLObject.h"
namespace Lumos {

    class Shader : public GLObject
    {
    public:
        Shader();
        virtual ~Shader(){};

        static const std::string default_mesh_shader_id;
        static const std::string default_bbox_shader_id;
        static const std::string depth_shader_id;
        static const std::string mask_shader_id;
        static const std::string selected_instances_shader_id;

        /**
         * @brief ask openGL to return a list of uniforms and varyings attached of the shaders attached to the program
         * @param varyings, will be loaded with varyings
         * @param uniforms, will be loaded with uniforms
         */
        static void getCurrentVaryingsAndUniforms( std::vector<std::string> & varyings, std::vector<std::string> & uniforms);

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

        /**
         * @brief wrapper class to provide access to OpenGL
         */
        void use() const override;
        void stopUsing() const override;

        bool isInUse() const;


    protected:


    private:
        /**
         * @brief Shader
         * @param filePath file path to the GLSL file
         * @param shaderType type of shader
         *        must be one of
         *        GL_COMPUTE_SHADER | GL_VERTEX_SHADER |
         *        GL_TESS_CONTROL_SHADER | GL_TESS_EVALUATION_SHADER |
         *        GL_Mesh_SHADER | GL_FRAGMENT_SHADER
         */
        Shader(const std::string & filePath, const GLenum & shaderType );

        std::vector<std::string> _uniforms;
        std::vector<std::string> _varyings;



    };


}

	#endif
