#ifndef MULTISAMPLEDDEPTHTEXBUFFER_H
  #define MULTISAMPLEDDEPTHTEXBUFFER_H

#include "Texture.h"

namespace Lumos{


class MultisampledDepthTexBuffer : public Texure{
public:
  MultisampledDepthTexBuffer();
  MultisampledDepthTexBuffer(const size_t & width, const size_t & height);
  void resize(const GLsizei & w, const GLsizei & h) override;
protected:

private:
};


}

  #endif
