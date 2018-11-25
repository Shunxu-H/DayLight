#ifndef TEXTURE2D_H
  #define TEXTURE2D_H

#include "Texture.h"

namespace Lumos{


class Texture2D : public Texture{
public:
  Texture2D();
  Texture2D( const cv::Mat & im,
            const GLint & internalFormat = GL_RGB,
            const GLint & dataType = GL_UNSIGNED_BYTE,
            const GLint & minMagFiler = GL_LINEAR,
            const GLint & wrapMode = GL_REPEAT
            );
  void resize(const GLsizei & w, const GLsizei & h) const override;

protected:

private:
};


}

  #endif
