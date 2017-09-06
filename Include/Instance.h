#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>
#include "GL_include.h"
#include "Color.h"
#include "Shader.h"
#include "View.h"


namespace Lumos {
    class ArrayBuffer;

    struct Material{
        color4 color;
        float reflexitivity;
        Material( const color4 & c = color4(1.0f, 1.0f, 1.0f, 1.0f),
                  const float & r = 0.3
                ):color(c), reflexitivity(r){}
    };

    struct ModelAsset {
        Shader shaders;
        Material* material;
        GLuint VAO;
        GLuint VBO_VERT;
        GLuint VBO_NORMAL;
        GLuint VBO_COLOR;
        GLenum drawType;
        GLint drawStart;
        GLint drawCount;
    };

    class Instance{
    public:
        Instance(){}
        Instance( const glm::mat4 & modelMatrix, const ModelAsset & asset );

        virtual ~Instance(){}

        void render( const View & v ) const;

        /**
         * @brief setter and getter for private members
         */
        inline void
            setModelMatrix( const glm::mat4 & m ) { _modelMatrix = m; }
        inline void
            setAsset( const ModelAsset & m ) { _asset = m; }

        inline glm::mat4
            getModelMatrix() const { return _modelMatrix; }
        inline ModelAsset
            getAsset() const { return _asset; }

    protected:

    private:
        glm::mat4 _modelMatrix;
        ModelAsset _asset;

    };
}

#endif // INSTANCE_H
