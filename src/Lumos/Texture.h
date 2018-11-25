/*
The MIT License (MIT)

Copyright (c) 2016-2018, Shunxu Huang, shunxuhuang@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#ifndef TEXTURE_H
  #define TEXTURE_H

#include "GLObject.h"

namespace Lumos{

  class Texture: public GLObject{
  public:
    /**
     * STATIC FUNCTIONS
     */
    inline static GLint getMaximumSampleSize() {
      int samples;
      //We need to find out what the maximum supported samples is
      glGetIntegerv(GL_MAX_SAMPLES_EXT, &samples);
      return samples;
    }
    static const GLint DEFAULTSAMPLESIZE;

    Texture();
    virtual ~Texture();

    void use() const override;
    bool isInUse() const override;
    void stopUsing() const override;

    inline size_t getWidth() const {
      use();
      int w, miplevel = 0;
      glGetTexLevelParameteriv(_textureTarget, miplevel, GL_TEXTURE_WIDTH, &w);
      stopUsing();
      return w;
    }
    inline size_t getHeight() const{
      use();
      int h, miplevel = 0;
      glGetTexLevelParameteriv(_textureTarget, miplevel, GL_TEXTURE_HEIGHT, &h);
      stopUsing();
      return h;
    }
    inline GLenum getTarget() const
      { return _textureTarget; }
    inline bool isInitialized() const
      { return _textureTarget != 0; }

    virtual void resize(const GLsizei & w, const GLsizei & h) const = 0;
    // void make2DTexure(const cvt size_t & h);

  protected:
    GLenum _textureTarget;
    GLint _internalFormat;
    GLenum _dataType;

  private:
  };


}


#endif
