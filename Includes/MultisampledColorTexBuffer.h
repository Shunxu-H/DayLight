#ifndef MULTISAMPLEDCOLORTEXBUFFER_H
  #define MULTISAMPLEDCOLORTEXBUFFER_H

#include "Texture.h"

namespace Lumos{


class MultisampledColorTexBuffer : public Texure{
public:
  MultisampledColorTexBuffer();
  MultisampledColorTexBuffer(const size_t & width, const size_t & height);
  void resize(const GLsizei & w, const GLsizei & h) override;
protected:

private:
};


}

  #endif
