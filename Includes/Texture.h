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
