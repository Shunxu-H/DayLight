#ifndef COLORTEXBUFFER_H
  #define COLORTEXBUFFER_H

#include "Texture.h"

namespace Lumos{


class ColorTexBuffer : public Texure{
public:
  ColorTexBuffer();
  ColorTexBuffer(const size_t & width, const size_t & height);
  void resize(const GLsizei & w, const GLsizei & h) override;
protected:

private:
};


}

  #endif
