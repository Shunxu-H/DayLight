#include "Utility.h"
#include "MultisampledFrameBuffer.h"


namespace Lumos{

MultisampledFrameBuffer::MultisampledFrameBuffer(){}

MultisampledFrameBuffer::MultisampledFrameBuffer(const size_t & width, const size_t & height)
  : FrameBuffer(width, height)
  , _outputBuffer(width, height)
{
  _colorTexBuffer.makeMultisampledColorTextureBuffer(_width, _height);
  _depthTexBuffer.makeMultisampledDepthTextureBuffer(_width, _height);
}

MultisampledFrameBuffer & MultisampledFrameBuffer::operator = ( const MultisampledFrameBuffer & that)
{
  FrameBuffer_base::operator=(that);
  _outputBuffer = that._outputBuffer;
  return *this;
}

cv::Mat MultisampledFrameBuffer::saveColorBuffer2file(const std::string & filename)
{
  GLError( __PRETTY_FUNCTION__ , __LINE__ );
  use(GL_READ_FRAMEBUFFER);

  GLError( __PRETTY_FUNCTION__ , __LINE__ );
  _outputBuffer.use(GL_DRAW_FRAMEBUFFER);
  GLError( __PRETTY_FUNCTION__ , __LINE__ );
  glBlitFramebuffer(  0,
                      0,
                      _width,
                      _height,
                      0,
                      0,
                      _width,
                      _height,
                      GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
                      GL_NEAREST
                    );
  return _outputBuffer.saveColorBuffer2file(filename);
}

cv::Mat MultisampledFrameBuffer::saveDepthBuffer2file(const std::string & filename)
{
  GLError( __PRETTY_FUNCTION__ , __LINE__ );
  use(GL_READ_FRAMEBUFFER);

  GLError( __PRETTY_FUNCTION__ , __LINE__ );
  _outputBuffer.use(GL_DRAW_FRAMEBUFFER);

  glBlitFramebuffer(  0,
                      0,
                      _width,
                      _height,
                      0,
                      0,
                      _width,
                      _height,
                      GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
                      GL_NEAREST
                    );
  return _outputBuffer.saveDepthBuffer2file(filename);
}

void MultisampledFrameBuffer::resize(const size_t & width, const size_t & height)
{
  assert("You will eventually have to build this, buddy");
}






}
