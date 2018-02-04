
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
#include "FrameBuffer_base.h"

namespace Lumos{

FrameBuffer_base::FrameBuffer_base()
    : GLObject( [](GLuint * id){glGenFramebuffers(1, id);},
                [](const GLuint * id){glDeleteFramebuffers(1, id);} )
{
    //_initialize(_width, _height);

}

FrameBuffer_base::~FrameBuffer_base()
{

}

void FrameBuffer_base::use(const GLenum & target) const
{
    assert ((target == GL_FRAMEBUFFER or
             target == GL_READ_FRAMEBUFFER or
             target == GL_DRAW_FRAMEBUFFER )
             and
             "Target can only be GL_READ_FRAMEBUFFER, GL_DRAW_FRAMEBUFFER,\
             or GL_FRAMEBUFFER (for binding of both read and draw buffer)"
           );

    glBindFramebuffer(target, _glObjId);
}

void FrameBuffer_base::use() const
{
  glBindFramebuffer(GL_FRAMEBUFFER, _glObjId);
}

bool FrameBuffer_base::isInUse(const GLint & bindingTarget ) const {
    assert((bindingTarget == GL_DRAW_FRAMEBUFFER_BINDING or
            bindingTarget == GL_READ_FRAMEBUFFER_BINDING) and
            "bindingTarget is either GL_DRAW_FRAMEBUFFER_BINDING or GL_READ_FRAMEBUFFER_BINDING"
          );

    GLint fbid = 0;
    glGetIntegerv(bindingTarget, &fbid);
    return fbid == static_cast<GLint>(_glObjId);
}

bool FrameBuffer_base::isInUse() const
{
  assert(!"Please use FrameBuffer_base::isInUse(const GLint & bindingTarget ) const" );
  GLint fbid = 0;
  glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &fbid);
  return fbid == static_cast<GLint>(_glObjId);
}



void FrameBuffer_base::stopUsing() const
{
    if(isInUse(GL_DRAW_FRAMEBUFFER_BINDING))
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    if(isInUse(GL_READ_FRAMEBUFFER_BINDING))
        glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

}


}
