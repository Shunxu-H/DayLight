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
#ifndef TEXTURE_H
  #define TEXTURE_H

#include "GLObject.h"

namespace Lumos{

    class Texture: public GLObject{
    public:
        Texture();
        Texture(const Texture & that)=delete; // mark to remember to build
        Texture & operator = (const Texture & that );
        virtual ~Texture();

        void use() const override;
        bool isInUse() const override;
        void stopUsing() const override;

        inline size_t getWidth() const {
          int w, miplevel = 0;
          glGetTexLevelParameteriv(_textureTarget, miplevel, GL_TEXTURE_WIDTH, &w);
          return w;
        }
        inline size_t getHeight() const{
          int h, miplevel = 0;
          glGetTexLevelParameteriv(_textureTarget, miplevel, GL_TEXTURE_HEIGHT, &h);
          return h;
        }
        inline GLenum getTarget() const
          { return _textureTarget; }
        inline bool isInitialized() const
          { return _textureTarget != 0; }

        virtual void resize(const GLsizei & w, const GLsizei & h) const = 0;
        void make2DTexure(const cv::Mat & im,
                          const GLint & internalFormat = GL_RGB,
                          const GLint & dataType = GL_UNSIGNED_BYTE,
                          const GLint & minMagFiler = GL_LINEAR,
                          const GLint & wrapMode = GL_REPEAT
                          );
        void makeMultisampledColorTextureBuffer(const size_t & w,
                                                const size_t & h,
                                                const GLint & internalFormat = GL_RGBA,
                                                const size_t & sampleSize=16);
        void makeMultisampledDepthTextureBuffer(const size_t & w,
                                                const size_t & h,
                                                const GLint & internalFormat = GL_DEPTH_COMPONENT32F,
                                                const size_t & sampleSize=16);
        void makeColorTextureBuffer(const size_t & w,
                                    const size_t & h);
        void makeDepthTextureBuffer(const size_t & w,
                                    const size_t & h);

    protected:

    private:
        GLenum _textureTarget;
        GLint _internalFormat;
        GLenum _dataType;
    };


}


#endif
