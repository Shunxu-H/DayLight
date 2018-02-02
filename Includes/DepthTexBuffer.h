#ifndef DEPTHTEXBUFFER_H
  #define DEPTHTEXBUFFER_H

#include "Texture.h"

namespace Lumos{


class DepthTexBuffer : public Texure{
public:
  DepthTexBuffer();
  DepthTexBuffer(const size_t & width, const size_t & height);
  void resize(const GLsizei & w, const GLsizei & h) override;
protected:

private:
};


}

  #endif
