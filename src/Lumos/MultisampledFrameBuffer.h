#ifndef MULTISAMPLEDFRAMEBUFFER_H
  #define MULTISAMPLEDFRAMEBUFFER_H

#include "FrameBuffer_base.h"
#include "FrameBuffer.h"
#include "MultisampledColorTexBuffer.h"
#include "MultisampledDepthTexBuffer.h"

namespace Lumos{
  class MultisampledFrameBuffer : public FrameBuffer_base{
  public:
    MultisampledFrameBuffer();
    MultisampledFrameBuffer(const size_t & width, const size_t & height);
    MultisampledFrameBuffer(const FrameBuffer & outputBuffer);
    MultisampledFrameBuffer & operator = ( const MultisampledFrameBuffer & that);

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

    MultisampledColorTexBuffer _colorTexBuffer;
    MultisampledDepthTexBuffer _depthTexBuffer;
    FrameBuffer _outputBuffer;

    void _initialize() const;
  };

}


  #endif
