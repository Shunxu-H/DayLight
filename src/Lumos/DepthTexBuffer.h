#pragma once 

#include "Texture.h"

namespace Daylight::Lumos{


class DepthTexBuffer : public Texture{
public:
  DepthTexBuffer();
  DepthTexBuffer(const size_t & width, const size_t & height);
  void resize(const GLsizei & w, const GLsizei & h) const override;
protected:

private:
};


}

