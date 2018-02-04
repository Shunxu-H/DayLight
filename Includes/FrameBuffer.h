#ifndef FRAMEBUFFER_H
  #define FRAMEBUFFER_H

#include "GL_include.h"
#include "FrameBuffer_base.h"
#include "ColorTexBuffer.h"
#include "DepthTexBuffer.h"
namespace Lumos{

class FrameBuffer : public FrameBuffer_base{
public:
  FrameBuffer(){};
  FrameBuffer(const size_t & width, const size_t & height);
  virtual ~FrameBuffer();

  /**
   * GETTER AND SETTER
   */
  inline size_t getHeight() const{ return _colorTexBuffer.getHeight(); }
  inline size_t getWidth() const {  return _colorTexBuffer.getWidth(); }

  cv::Mat saveColorBuffer2file(const std::string & filename) override;
  cv::Mat saveDepthBuffer2file(const std::string & filename) override;
  void resize(const size_t & width, const size_t & height) override;
protected:

private:
  ColorTexBuffer _colorTexBuffer;
  DepthTexBuffer _depthTexBuffer;

};


}




  #endif
