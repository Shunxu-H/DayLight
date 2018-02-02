#ifndef MULTISAMPLEDFRAMEBUFFER_H
  #define MULTISAMPLEDFRAMEBUFFER_H

#include "FrameBuffer_base.h"
#include "FrameBuffer.h"

namespace Lumos{
  class MultisampledFrameBuffer : public FrameBuffer{
  public:
    MultisampledFrameBuffer();
    MultisampledFrameBuffer(const size_t & width, const size_t & height);
    MultisampledFrameBuffer & operator = ( const MultisampledFrameBuffer & that);

    cv::Mat saveColorBuffer2file(const std::string & filename) override;
    cv::Mat saveDepthBuffer2file(const std::string & filename) override;
    void resize(const size_t & width, const size_t & height) override;
  protected:

  private:
    FrameBuffer _outputBuffer;
  };

}


  #endif
