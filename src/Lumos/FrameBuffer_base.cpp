#include "FrameBuffer_base.h"

using namespace Lumos;

FrameBuffer_base::FrameBuffer_base(const size_t & w_, const size_t & h_)
    : GLObject( [](GLuint * id){glGenFramebuffers(1, id);},
                [](const GLuint * id){glDeleteFramebuffers(1, id);} )
    , _width(w_)
    , _height(h_)
{
    _initialize(_width, _height);

}

FrameBuffer_base & FrameBuffer_base::operator = (const FrameBuffer_base & that)
{
    GLObject::operator = (that);
    this->_colorTexBuffer = that._colorTexBuffer;
    this->_depthTexBuffer = that._depthTexBuffer;
    return *this;
}

FrameBuffer_base::~FrameBuffer_base()
{

}


void FrameBuffer_base::_initialize(const size_t & w, const size_t & h)
{
    assert(not _colorTexBuffer.isInitialized() and
           not _depthTexBuffer.isInitialized() and
           "This FrameBuffer has been made"
          );

    _colorTexBuffer.makeColorTextureBuffer(w, h);
    _depthTexBuffer.makeDepthTextureBuffer(w, h);
}

// void FrameBuffer::makeMultisampledFrameBuffer(const size_t & w, const size_t & h)
// {
//     assert(not _colorTexBuffer.isInitialized() and
//            not _depthTexBuffer.isInitialized() and
//            "This FrameBuffer has been made"
//           );
//
//     _colorTexBuffer.makeMultisampledColorTextureBuffer(w, h);
//     _depthTexBuffer.makeMultisampledDepthTextureBuffer(w, h);
// }

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

bool FrameBuffer_base::isInUse(const GLint & bindingTarget ) const {
    assert((bindingTarget == GL_DRAW_FRAMEBUFFER_BINDING or
            bindingTarget == GL_READ_FRAMEBUFFER_BINDING) and
            "bindingTarget is either GL_DRAW_FRAMEBUFFER_BINDING or GL_READ_FRAMEBUFFER_BINDING"
          );

    GLint fbid = 0;
    glGetIntegerv(bindingTarget, &fbid);
    return fbid == static_cast<GLint>(_glObjId);
}

void FrameBuffer_base::use() const
{
    assert(!"Please do not call this function");
}

bool FrameBuffer_base::isInUse() const
{
    assert(!"Please do not call this function");
    return true; // to avoid compilation error
}

void FrameBuffer_base::stopUsing() const
{
    if(isInUse(GL_DRAW_FRAMEBUFFER_BINDING))
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    if(isInUse(GL_READ_FRAMEBUFFER_BINDING))
        glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

}
