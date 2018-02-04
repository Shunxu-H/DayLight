#include "Texture2D.h"

namespace Lumos{


Texture2D::Texture2D()
{

}

Texture2D::Texture2D( const cv::Mat & img,
                      const GLint & internalFormat,
                      const GLint & dataType,
                      const GLint & minMagFiler,
                      const GLint & wrapMode)
{
  assert(_glObjId != 0); // make sure object is initialized
  assert(!img.empty()); // make sure it is a valid image

  _textureTarget = GL_TEXTURE_2D;
  _internalFormat = internalFormat;
  _dataType = dataType;

  glBindTexture(_textureTarget,  _glObjId);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minMagFiler);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minMagFiler);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
  glTexImage2D(GL_TEXTURE_2D,        // Type of texture
               0,                    // Pyramid level (for mip-mapping) - 0 is the top level
               _internalFormat,      // Internal colour format to convert to
               img.cols,              // Image width
               img.rows,              // Image height
               0,                    // Border width in pixels (can either be 1 or 0)
               GL_BGR,               // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
               _dataType,            // Image data type
               img.ptr());
}

void Texture2D::resize(const GLsizei & w, const GLsizei & h) const
{
  assert(!"it will be a mistake to use this, I know, I didnt think through the architecutre, I am sorry ");
  use();
  assert(w > 0 and h > 0 and "Width and Height must be positive");
  glTexImage2D(GL_TEXTURE_2D,        // Type of texture
             0,                    // Pyramid level (for mip-mapping) - 0 is the top level
             _internalFormat,      // Internal colour format to convert to
             getHeight(),              // Image width
             getWidth(),              // Image height
             0,                    // Border width in pixels (can either be 1 or 0)
             GL_BGR,               // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
             _dataType,            // Image data type
             0);
stopUsing();

}

}