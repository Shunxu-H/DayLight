#ifndef MULTISAMPLEDDEPTHTEXBUFFER_H
  #define MULTISAMPLEDDEPTHTEXBUFFER_H

#include "Texture.h"

namespace Lumos{


class MultisampledDepthTexBuffer : public Texture{
public:
  MultisampledDepthTexBuffer();
  MultisampledDepthTexBuffer(const size_t & width, const size_t & height, const GLint & sampleSize);

  void resize(const GLsizei & w, const GLsizei & h) const override;
protected:
  GLint _sampleSize;
private:
};


}

  #endif
