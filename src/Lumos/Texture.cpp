
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
#include "Texture.h"
#include "Common/Utility.h"

using namespace Daylight::Lumos; 


const GLint Texture::DEFAULTSAMPLESIZE = 4;

/**
 * target
   GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_3D, GL_TEXTURE_1D_ARRAY, GL_TEXTURE_2D_ARRAY, GL_TEXTURE_RECTANGLE, GL_TEXTURE_CUBE_MAP, GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_BUFFER, GL_TEXTURE_2D_MULTISAMPLE or GL_TEXTURE_2D_MULTISAMPLE_ARRAY.

 */
Texture::Texture()
    : GLObject( [](GLuint * id){glGenTextures(1, id);},
                [](const GLuint * id){glDeleteTextures(1, id);} )
    , _textureTarget(0)
    , _internalFormat(0)
    , _dataType(0)
{


}

// void Texture::make2DTexure( const cv::Mat & im,
//                             const GLint & internalFormat,
//                             const GLint & dataType,
//                             const GLint & minMagFiler,
//                             const GLint & wrapMode)
// {
//     assert(_glObjId != 0); // make sure object is initialized
//     assert(!im.empty()); // make sure it is a valid image
//
//     _textureTarget = GL_TEXTURE_2D;
//     _internalFormat = internalFormat;
//     _dataType = dataType;
//
//     glBindTexture(_textureTarget,  _glObjId);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minMagFiler);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minMagFiler);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
//     glTexImage2D(_textureTarget,       // Type of texture
//                  0,                    // Pyramid level (for mip-mapping) - 0 is the top level
//                  _internalFormat,      // Internal colour format to convert to
//                  im.cols,              // Image width
//                  im.rows,              // Image height
//                  0,                    // Border width in pixels (can either be 1 or 0)
//                  GL_BGR,               // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
//                  _dataType,            // Image data type
//                  im.ptr());
//
// }

Texture::~Texture()
{

}



void Texture::resize(const GLsizei & w, const GLsizei & h) const{
  use();
  assert(w > 0 and h > 0 and "Width and Height must be positive");
  glTexImage2D (_textureTarget,
                0,
                _internalFormat,
                w,
                h,
                0,
                GL_RED,
                GL_FLOAT,
                NULL);
  stopUsing();
}
//
// void Texture::makeMultisampledColorTextureBuffer(const size_t & w,
//                                                  const size_t & h,
//                                                  const GLint & internalFormat,
//                                                  const size_t & sampleSize)
// {
//     // make sure the object is not initialized
//     assert(_glObjId != 0 && "GLObject initialization probably failed.");
//     assert(_textureTarget == 0);
//     _textureTarget = GL_TEXTURE_2D_MULTISAMPLE;
//     _internalFormat = GL_RGBA;
//
//     GLError( __PRETTY_FUNCTION__ , __LINE__ );
//
//     int samples;
//     //We need to find out what the maximum supported samples is
//     glGetIntegerv(GL_MAX_SAMPLES_EXT, &samples);
//     //----------------------
//     //If for example, 16 is returned, then you can attempt to make a FBO with samples=0 to 16
//     //0 means no multisample. This is like using glFramebufferRenderbufferEXT instead of glRenderbufferStorageMultisampleEXT
//     //You can attempt to make sample from 1 to 16, but some of them might fail
//     //Now, let's make a FBO
//     assert( samples >= static_cast<int>(sampleSize) && "Multisampler requisition failed.");
//
//     GLError( __PRETTY_FUNCTION__ , __LINE__ );
//     //----------------------
//     //Now make a multisample color buffer
//     //glGenRenderbuffers(1, &_Multisampled_ColorBuffer);
//     //glBindRenderbuffer(GL_RENDERBUFFER, _Multisampled_ColorBuffer);
//     //samples=4, format=GL_RGBA8, width=256, height=256
//     //glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_RGBA8, _width, _height);
//     use();
//     glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE,
//                             sampleSize,
//                             _internalFormat,
//                             w,
//                             h,
//                             GL_FALSE);
//
//     stopUsing();
//     GLError( __PRETTY_FUNCTION__ , __LINE__ );
//
// }
//
// void Texture::makeMultisampledDepthTextureBuffer(const size_t & w,
//                                                  const size_t & h,
//                                                  const GLint & internalFormat,
//                                                  const size_t & sampleSize)
// {
//     // make sure the object is not initialized
//     assert(_glObjId != 0 && "GLObject initialization probably failed.");
//     assert(_textureTarget == 0);
//     _textureTarget = GL_TEXTURE_2D_MULTISAMPLE;
//     _internalFormat = internalFormat;
//     GLError( __PRETTY_FUNCTION__ , __LINE__ );
//
//     int samples;
//     //We need to find out what the maximum supported samples is
//     glGetIntegerv(GL_MAX_SAMPLES_EXT, &samples);
//     //----------------------
//     //If for example, 16 is returned, then you can attempt to make a FBO with samples=0 to 16
//     //0 means no multisample. This is like using glFramebufferRenderbufferEXT instead of glRenderbufferStorageMultisampleEXT
//     //You can attempt to make sample from 1 to 16, but some of them might fail
//     //Now, let's make a FBO
//     assert( samples >= static_cast<int>(sampleSize) && "Multisampler requisition failed.");
//
//     GLError( __PRETTY_FUNCTION__ , __LINE__ );
//     //----------------------
//     //Now make a multisample color buffer
//     //glGenRenderbuffers(1, &_Multisampled_ColorBuffer);
//     //glBindRenderbuffer(GL_RENDERBUFFER, _Multisampled_ColorBuffer);
//     //samples=4, format=GL_RGBA8, width=256, height=256
//     //glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_RGBA8, _width, _height);
//     use();
//     glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE,
//                             samples,
//                             GL_DEPTH_COMPONENT32F,
//                             w,
//                             h,
//                             GL_FALSE);
//
//     stopUsing();
//     GLError( __PRETTY_FUNCTION__ , __LINE__ );
//
// }
//
// void Texture::makeColorTextureBuffer(const size_t & w, const size_t & h){
//     assert(_glObjId != 0 && "GLObject initialization probably failed.");
//     assert(_textureTarget == 0);
//     _textureTarget = GL_TEXTURE_2D;
//
//     GLError( __PRETTY_FUNCTION__ , __LINE__ );
//
//     use();
//     glTexParameteri(_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     glTexParameteri(_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexImage2D(_textureTarget,
//                  0,
//                  GL_RGBA,
//                  w,
//                  h,
//                  0,
//                  GL_RGBA,
//                  GL_UNSIGNED_BYTE,
//                  NULL);
//
//     stopUsing();
//     GLError( __PRETTY_FUNCTION__ , __LINE__ );
//
// }
//
// void Texture::makeDepthTextureBuffer(const size_t & w, const size_t & h){
//     assert(_glObjId != 0 && "GLObject initialization probably failed.");
//     assert(_textureTarget == 0);
//     _textureTarget = GL_TEXTURE_2D;
//
//     GLError( __PRETTY_FUNCTION__ , __LINE__ );
//
//     use();
//     glTexParameteri(_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     glTexParameteri(_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexImage2D(GL_TEXTURE_2D,
//                  0,
//                  GL_DEPTH_COMPONENT32F,
//                  w,
//                  h,
//                  0,
//                  GL_DEPTH_COMPONENT,
//                  GL_FLOAT,
//                  NULL);
//
//     stopUsing();
//     GLError( __PRETTY_FUNCTION__ , __LINE__ );
// }


void Texture::use() const
{
    assert(_textureTarget != 0); // make sure the texture is initialized
    glBindTexture(_textureTarget, _glObjId);
}

bool Texture::isInUse() const
{
    GLint data;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &data);
    return static_cast<GLuint>( data ) == _glObjId;
}

void Texture::stopUsing() const
{
    glBindTexture(_textureTarget, _glObjId);
}
