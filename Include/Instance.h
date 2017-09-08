#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>
#include "GL_include.h"
#include "Transformable.h"
#include "Color.h"
#include "Shader.h"
#include "View.h"
#include "ModelAsset.h"

namespace Patronus {
    class Mesh;
}
namespace Lumos {
    class ArrayBuffer;


    class Instance: public Patronus::Transformable{
    public:
        Instance(){}
        Instance( Patronus::Mesh * meshPtr,
                  const ModelAsset & asset
                  );

        virtual ~Instance(){}

        /**
         * @brief bind data to attributes and uniforms of the shaders currently binded to openGL
         */
        void loadAttribsAndUniform( const View & view ) const;

        void renderMesh( const View & v ) const;

        void renderBoundngBox( const View & v) const;


        /**
         * @brief setter and getter for private members
         */
        inline void
            setMeshAsset( ModelAsset asset ) { _asset = asset; }

        inline ModelAsset
            getMeshAsset() const { return _asset; }

    protected:

    private:
        ModelAsset _asset;
        Patronus::Mesh * _meshPtr;



    };
}

#endif // INSTANCE_H
