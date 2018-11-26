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
#ifndef MODELASSET_H
#define MODELASSET_H

#include "Common/GL_include.h"
#include "Material.h"

/**
 * @TODO: Make Texture a separated class
 */
namespace Lumos {


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
