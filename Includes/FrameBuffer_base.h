
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
#ifndef FRAMEBUFFER_BASE_H
  #define FRAMEBUFFER_BASE_H

#include "GLObject.h"
#include "Texture.h"

namespace Lumos
{
    class FrameBuffer_base: public GLObject{
    public:
        FrameBuffer_base(const size_t & w_ = 0,
                    const size_t & h_ = 0);
        FrameBuffer_base & operator = (const FrameBuffer_base & that);
        virtual ~FrameBuffer_base();

        void use(const GLenum & target = GL_FRAMEBUFFER) const ;
        bool isInUse(const GLint & bindingTarget = GL_DRAW_FRAMEBUFFER_BINDING ) const;
        void stopUsing() const override;


        void blit( const FrameBuffer_base  & that ) const;
        //void makeMultisampledFrameBuffer(const size_t & w, const size_t & h);

        /**
         * it saves the current pixels to a file
         * @param  filename the name for the output files, if it is undefined,
         *         then it won't be saved on the disk
         * @return the pixels on the buffer represented with a
         */
        virtual cv::Mat save2file(const std::string & filename) const = 0;
    protected:
        size_t _width;
        size_t _height;
        Texture _colorTexBuffer;
        Texture _depthTexBuffer;
    private:
        bool isInUse() const override; // to disable isInUse
        void use() const override; // to disable use

        virtual void _initialize(const size_t & w, const size_t & h) = 0;
    };

}

#endif
