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


        void blit( const FrameBuffer_base  & that ) const ;
        //void makeMultisampledFrameBuffer(const size_t & w, const size_t & h);

    protected:

    private:
        bool isInUse() const override; // to disable isInUse
        void use() const override; // to disable use

        virtual void _initialize(const size_t & w, const size_t & h);
        size_t _width;
        size_t _height;
        Texture _colorTexBuffer;
        Texture _depthTexBuffer;
    };

}

#endif
