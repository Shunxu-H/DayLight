#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>
#include "GL_include.h"
#include "Color.h"
#include "Shader.h"
#include "ArrayBuffer.h"

namespace Lumos {
    struct Material{
        color4 color;
        float reflexitivity;
        Material():color(color4(1.0f, 1.0f, 1.0f, 1.0f)), reflexitivity(0.3){}
    };

    struct ModelAsset {
        Shader shaders;
        Material material;
        GLuint _VAO;
        std::vector<ArrayBuffer> _VBOs;
        GLenum drawType;
        GLint drawStart;
        GLint drawCount;
    };

    class Instance{
    public:

    protected:

    private:
        glm::mat4 _modelMatrix;
        ModelAsset _asset;

    };
}

#endif // INSTANCE_H
