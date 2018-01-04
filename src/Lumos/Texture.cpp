#include "Texture.h"


using namespace Lumos;


/**
 * target
   GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_3D, GL_TEXTURE_1D_ARRAY, GL_TEXTURE_2D_ARRAY, GL_TEXTURE_RECTANGLE, GL_TEXTURE_CUBE_MAP, GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_BUFFER, GL_TEXTURE_2D_MULTISAMPLE or GL_TEXTURE_2D_MULTISAMPLE_ARRAY.

 */
Texture::Texture(cv::Mat im)
    : GLObject( [](GLuint * id){glGenTextures(1, id);},
                [](const GLuint * id){glDeleteTextures(1, id);} )
    , _textureTarget(0)
{


}

void Texture::make2DTexure( const cv::Mat & im,
                          const GLint & minMagFiler,
                          const GLint & wrapMode)
{
    assert(_glObjId != 0); // make sure object is initialized
    assert(!im.empty()); // make sure it is a valid image

    _textureTarget = GL_TEXTURE_2D;

    glBindTexture(_textureTarget,  _glObjId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minMagFiler);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minMagFiler);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    glTexImage2D(GL_TEXTURE_2D,     // Type of texture
                     0,                 // Pyramid level (for mip-mapping) - 0 is the top level
                     GL_RGB,            // Internal colour format to convert to
                     im.cols,          // Image width  i.e. 640 for Kinect in standard mode
                     im.rows,          // Image height i.e. 480 for Kinect in standard mode
                     0,                 // Border width in pixels (can either be 1 or 0)
                     GL_BGR, // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
                     GL_UNSIGNED_BYTE,  // Image data type
                     im.ptr());

}


Texture::~Texture()
{

}

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
