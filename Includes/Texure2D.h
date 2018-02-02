#ifndef TEXTURE2D_H
  #define TEXTURE2D_H

#include "Texture.h"

namespace Lumos{


class Texure2D : public Texure{
public:
  Texure2D();
  Texure2D(const size_t & width, const size_t & height);
  void resize(const GLsizei & w, const GLsizei & h) override;

protected:

private:
};


}

  #endif
