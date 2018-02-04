#ifndef MULTISAMPLEDCOLORTEXBUFFER_H
  #define MULTISAMPLEDCOLORTEXBUFFER_H

#include "Texture.h"

namespace Lumos{


class MultisampledColorTexBuffer : public Texture{
public:
  MultisampledColorTexBuffer();
  MultisampledColorTexBuffer(const size_t & width, const size_t & height, const GLint & sampleSize);
  void resize(const GLsizei & w, const GLsizei & h) const override;
protected:
  GLint _sampleSize;
private:
};


}

  #endif
