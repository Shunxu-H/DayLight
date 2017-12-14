/*
The MIT License (MIT)

Copyright (c) 2016-2017 Shunxu Huang

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
#ifndef MODELASSET_H
#define MODELASSET_H

#include "GL_include.h"
#include "GL_include.h"
#include <opencv2/opencv.hpp>

/**
 * @TODO: Make Texture a separated class
 */
namespace Lumos {
    struct Material{
        float reflexitivity;
        std::string id;
        color3 transmittance;
        color3 specular;
        color4 diffuseColor;
        GLuint glTexId;
        cv::Mat texture;
        Material( const color4 & c = color4(1.0f, 1.0f, 1.0f, 1.0f),
                  const float & reflexitivity_ = 0.3
                ): reflexitivity(reflexitivity_), diffuseColor(c), glTexId(0){}

        ~Material(){

        }
        void loadUniforms() const;

    };

    struct MaterialPack{
        Material * material;
        GLuint drawStart;
        GLuint drawCnt;
        MaterialPack(Material * m_, const GLuint & drawStart_, const GLuint & drawCnt_ )
            :material(m_), drawStart( drawStart_ ), drawCnt (drawCnt_ )
            {}
    };

    struct ModelAsset {
        std::string shaderId;
        std::vector<MaterialPack> materials;
        GLuint VBO_VERT;
        GLuint VBO_NORMAL;
        GLuint VBO_TEXCOORD;
        GLuint VBO_COLOR;
        GLenum drawType;
        GLint drawStart;
        GLint drawCount;
    };
}

#endif // MODELASSET_H
