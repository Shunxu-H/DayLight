 #include "Common/Utility.h"
#include "MultisampledFrameBuffer.h"


namespace Lumos{


MultisampledFrameBuffer::MultisampledFrameBuffer(){}

MultisampledFrameBuffer::MultisampledFrameBuffer(const size_t & width, const size_t & height)
  : FrameBuffer_base()
  , _colorTexBuffer(width, height, Texture::DEFAULTSAMPLESIZE)
  , _depthTexBuffer(width, height, Texture::DEFAULTSAMPLESIZE)
  , _outputBuffer(width, height)
{
  _initialize();
}

MultisampledFrameBuffer::MultisampledFrameBuffer(const FrameBuffer & outputBuffer)
  : FrameBuffer_base()
  , _colorTexBuffer(outputBuffer.getWidth(), outputBuffer.getHeight(), Texture::DEFAULTSAMPLESIZE)
  , _depthTexBuffer(outputBuffer.getWidth(), outputBuffer.getHeight(), Texture::DEFAULTSAMPLESIZE)
  , _outputBuffer(outputBuffer)
{
  _initialize();
}

MultisampledFrameBuffer & MultisampledFrameBuffer::operator = ( const MultisampledFrameBuffer & that)
{
  FrameBuffer_base::operator=(that);
  _colorTexBuffer = that._colorTexBuffer;
  _depthTexBuffer = that._depthTexBuffer;
  _outputBuffer = that._outputBuffer;
  return *this;
}

void MultisampledFrameBuffer::_initialize() const {

  assert(_colorTexBuffer.isInitialized() and _depthTexBuffer.isInitialized()
          and "_colorTexBuffer or _depthTexBuffer is not initialized properly");
  GLError( __PRETTY_FUNCTION__ , __LINE__ );

  use();

  //It's time to attach the RBs to the FBO
  glFramebufferTexture2D(GL_FRAMEBUFFER,
                         GL_COLOR_ATTACHMENT0,
                         GL_TEXTURE_2D_MULTISAMPLE,
                         _colorTexBuffer.getGlObjId(),
                         0);
  glFramebufferTexture2D(GL_FRAMEBUFFER,
                         GL_DEPTH_ATTACHMENT,
                         GL_TEXTURE_2D_MULTISAMPLE,
                         _depthTexBuffer.getGlObjId(),
                         0);
  //----------------------
  //Make sure FBO status is good

  GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
  glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
  char ErrorMessage[1024];
  if(Utils::glExtCheckFramebufferStatus(ErrorMessage) != 1){
      std::cerr << ErrorMessage << std::endl;
      exit(EXIT_FAILURE);
  }
  glEnable(GL_DEPTH_TEST);
  stopUsing();
  GLError( __PRETTY_FUNCTION__ , __LINE__ );
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
                      getWidth(),
                      getHeight(),
                      0,
                      0,
                      _outputBuffer.getWidth(),
                      _outputBuffer.getHeight(),
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
                      getWidth(),
                      getHeight(),
                      0,
                      0,
                      _outputBuffer.getWidth(),
                      _outputBuffer.getHeight(),
                      GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
                      GL_NEAREST
                    );
  GLError( __PRETTY_FUNCTION__ , __LINE__ );
  return _outputBuffer.saveDepthBuffer2file(filename);
}

void MultisampledFrameBuffer::resize(const size_t & width, const size_t & height)
{
  _colorTexBuffer.resize(width, height);
  _depthTexBuffer.resize(width, height);
  _outputBuffer.resize(width, height);
}






}
