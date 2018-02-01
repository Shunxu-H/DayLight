#ifndef FRAMEBUFFER_H
  #define FRAMEBUFFER_H

#include "GL_include.h"
#include "FrameBuffer_base.h"

namespace Lumos{

class FrameBuffer : public FrameBuffer_base{
public:
  FrameBuffer();
  FrameBuffer(const size_t & width, const size_t & height);
  FrameBuffer & operator = ( const FrameBuffer & that);
  virtual ~FrameBuffer();

  cv::Mat saveColorBuffer2file(const std::string & filename);
  cv::Mat saveDepthBuffer2file(const std::string & filename);
protected:

private:

};


}




  #endif
