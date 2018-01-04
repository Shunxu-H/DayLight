#ifndef TEXTURE_H
  #define TEXTURE_H

#include "GLObject.h"

namespace Lumos{


    class Texture: public GLObject{
    public:
        Texture(cv::Mat im=cv::Mat{});
        virtual ~Texture();

        void use() const override;
        bool isInUse() const override;
        void stopUsing() const override;

        inline GLenum getTarget() const
            { return _textureTarget; }
        inline bool isEmpty() const
            { return _textureTarget == 0; }

        void make2DTexure(const cv::Mat & im,
                          const GLint & minMagFiler
                                                = GL_LINEAR,
                          const GLint & wrapMode = GL_REPEAT
                          );
        void makeTexureBuffer(const size_t & w,
                              const size_t & h);

    protected:

    private:
        GLenum _textureTarget;
    };


}


#endif
