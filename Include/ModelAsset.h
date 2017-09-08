#ifndef MODELASSET_H
#define MODELASSET_H

namespace Lumos {
    struct Material{
        color4 color;
        float reflexitivity;
        Material( const color4 & c = color4(1.0f, 1.0f, 1.0f, 1.0f),
                  const float & r = 0.3
                ):color(c), reflexitivity(r){}
    };

    struct ModelAsset {
        std::string shaderId;
        Material* material;
        GLuint VAO;
        GLuint VBO_VERT;
        GLuint VBO_NORMAL;
        GLuint VBO_COLOR;
        GLenum drawType;
        GLint drawStart;
        GLint drawCount;
    };
}

#endif // MODELASSET_H
