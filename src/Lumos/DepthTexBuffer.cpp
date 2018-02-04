#include "DepthTexBuffer.h"
#include "Utility.h"
namespace Lumos{


DepthTexBuffer::DepthTexBuffer(){

}

DepthTexBuffer::DepthTexBuffer(const size_t & width, const size_t & height)
  : Texture()
{
  assert(_glObjId != 0 && "GLObject initialization probably failed.");
  assert(_textureTarget == 0);
  _textureTarget = GL_TEXTURE_2D;
  _internalFormat = GL_DEPTH_COMPONENT;
  _dataType = GL_UNSIGNED_BYTE;
  GLError( __PRETTY_FUNCTION__ , __LINE__ );

  use();
  glTexImage2D(_textureTarget,
               0,
               _internalFormat,
               width,
               height,
               0,
               GL_DEPTH_COMPONENT,
               _dataType,
               NULL);

  stopUsing();
  GLError( __PRETTY_FUNCTION__ , __LINE__ );
}

void DepthTexBuffer::resize(const GLsizei & w, const GLsizei & h) const
{
  use();
  assert(w > 0 and h > 0 and "Width and Height must be positive");
  glTexImage2D (_textureTarget,
                0,
                _internalFormat,
                w,
                h,
                0,
                GL_DEPTH_COMPONENT,
                _dataType,
                NULL);
  stopUsing();
}

}
