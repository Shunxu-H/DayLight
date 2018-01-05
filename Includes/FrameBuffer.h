#ifndef FRAMEBUFFER_H
  #define FRAMEBUFFER_H

#include "GLObject.h"
#include "Texture.h"

namespace Lumos
{
    class Framebuffer: public GLObject{
    public:
        Framebuffer();
        virtual ~Framebuffer();

        void use() const override;
        bool isInUse() const override;
        void stopUsing() const override;

        inline GLenum getTarget() const
            { return _bufferTarget; }
        inline bool isEmpty() const
            { return _bufferTarget == 0; }


    protected:

    private:
        Texture _colorTexBuffer;
        Texture _depthTexBuffer; 
    };

}

#endif
