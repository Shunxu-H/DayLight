#pragma once 

#include "Texture.h"

namespace Daylight::Lumos{


class ColorTexBuffer : public Texture{
public:
  ColorTexBuffer();
  ColorTexBuffer(const size_t & width, const size_t & height);
  void resize(const GLsizei & w, const GLsizei & h) const override;
protected:

private:
};


}

