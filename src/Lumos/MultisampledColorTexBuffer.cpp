#include "MultisampledColorTexBuffer.h"
#include "Utility.h"
namespace Lumos{



MultisampledColorTexBuffer::MultisampledColorTexBuffer()
{

}

MultisampledColorTexBuffer::MultisampledColorTexBuffer(
      const size_t & width,
      const size_t & height,
      const GLint & sampleSize)
  : Texture()
  , _sampleSize(sampleSize)
{
  // make sure the object is not initialized
  assert(_glObjId != 0 && "GLObject initialization probably failed.");
  assert(_textureTarget == 0);
  _textureTarget = GL_TEXTURE_2D_MULTISAMPLE;
  _internalFormat = GL_RGBA;
  _dataType = GL_UNSIGNED_BYTE;

  GLError( __PRETTY_FUNCTION__ , __LINE__ );

  int samples = getMaximumSampleSize();
  //----------------------
  //If for example, 16 is returned, then you can attempt to make a FBO with samples=0 to 16
  //0 means no multisample. This is like using glFramebufferRenderbufferEXT instead of glRenderbufferStorageMultisampleEXT
  //You can attempt to make sample from 1 to 16, but some of them might fail
  //Now, let's make a FBO
  assert( samples >= _sampleSize && "Multisampler requisition failed.");

  GLError( __PRETTY_FUNCTION__ , __LINE__ );
  //----------------------
  //Now make a multisample color buffer
  //glGenRenderbuffers(1, &_Multisampled_ColorBuffer);
  //glBindRenderbuffer(GL_RENDERBUFFER, _Multisampled_ColorBuffer);
  //samples=4, format=GL_RGBA8, width=256, height=256
  //glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_RGBA8, _width, _height);
  use();
  glTexImage2DMultisample(_textureTarget,
                          _sampleSize,
                          _internalFormat,
                          width,
                          height,
                          GL_FALSE);

  stopUsing();
  GLError( __PRETTY_FUNCTION__ , __LINE__ );

}

void MultisampledColorTexBuffer::resize(const GLsizei & w, const GLsizei & h) const
{
  use();
  assert(w > 0 and h > 0 and "Width and Height must be positive");
  glTexImage2DMultisample(_textureTarget,
                          _sampleSize,
                          _internalFormat,
                          w,
                          h,
                          GL_FALSE);
  stopUsing();

}


}
