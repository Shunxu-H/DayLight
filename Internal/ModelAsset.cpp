#include "GL_include.h"
#include "ModelAsset.h"



using namespace Lumos;


GLenum Material::getBitmapFormat()
{
    switch (texture.format()) {
        case QImage::Format_Mono: return GL_LUMINANCE;
        //case Bitmap::Format_GrayscaleAlpha: return GL_LUMINANCE_ALPHA;
        case QImage::Format_RGB32: return GL_RGB;
        case QImage::Format_ARGB32: return GL_RGBA;
        default: throw std::runtime_error("Unrecognised Bitmap::Format");
    }
}
