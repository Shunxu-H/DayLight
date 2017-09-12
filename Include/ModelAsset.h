#ifndef MODELASSET_H
#define MODELASSET_H

#include "GL_include.h"
#include <QImage>

namespace Lumos {
    struct Material{
        float reflexitivity;
        std::string id;
        color4 diffuseColor;
        color3 transmittance;
        GLuint glTexId;
        QImage texture;
        Material( const color4 & c = color4(1.0f, 1.0f, 1.0f, 1.0f),
                  const float & reflexitivity_ = 0.3
                ): reflexitivity(reflexitivity_), diffuseColor(c), glTexId(0){}

        GLenum getBitmapFormat();
    };

    struct MaterialPack{
        Material * material;
        GLuint drawStart;
        GLuint drawCnt;
        MaterialPack(Material * m_, const GLuint & drawStart_, const GLuint & drawCnt_ )
            :material(m_), drawStart( drawStart_ ), drawCnt (drawCnt_ )
            {}
    };

    struct ModelAsset {
        std::string shaderId;
        std::vector<MaterialPack> materials;
        GLuint VAO;
        GLuint VBO_VERT;
        GLuint VBO_NORMAL;
        GLuint VBO_TEXCOORD;
        GLuint VBO_COLOR;
        GLenum drawType;
        GLint drawStart;
        GLint drawCount;
    };
}

#endif // MODELASSET_H
