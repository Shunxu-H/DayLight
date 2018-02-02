#include "ColorTexBuffer.h"

namespace Lumos{


ColorTexBuffer::ColorTexBuffer(){

}

ColorTexBuffer::ColorTexBuffer(const size_t & width, const size_t & height)
  : Texture(width, height)
{
  assert(_glObjId != 0 && "GLObject initialization probably failed.");
  assert(_textureTarget == 0);
  _textureTarget = GL_TEXTURE_2D;
  _internalFormat = GL_RGBA;
  _dataType = GL_UNSIGNED_BYTE;
  GLError( __PRETTY_FUNCTION__ , __LINE__ );

  use();
  glTexParameteri(_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(_textureTarget,
               0,
               GL_RGBA,
               w,
               h,
               0,
               GL_RGBA,
               GL_UNSIGNED_BYTE,
               NULL);

  stopUsing();
  GLError( __PRETTY_FUNCTION__ , __LINE__ );

}

void ColorTexBuffer::resize(const GLsizei & w, const GLsizei & h){
  use();
  assert(w > 0 and h > 0 and "Width and Height must be positive");
  glTexImage2D (_textureTarget,
                0,
                _internalFormat,
                w,
                h,
                0,
                _internalFormat,
                _dataType,
                NULL);
  stopUsing()
}




}
