#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>
#include "GL_include.h"
#include "Transformable.h"
#include "Color.h"
#include "Shader.h"
#include "View.h"
#include "ModelAsset.h"
#include "btBulletDynamicsCommon.h"

namespace Patronus {
    class Mesh;
}
namespace Lumos {
    class ArrayBuffer;


    class Instance: public Patronus::Transformable{
    public:
        Instance( Patronus::Mesh * meshPtr = nullptr,
                  const ModelAsset & asset = ModelAsset()
                  );

        virtual ~Instance();

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

        inline void
            setId( const std::string & id ) { _id = id; }
        inline std::string
            getId() const { return _id; }

        inline void
            setRidgidBody(  btRigidBody * const &  arg )
                { if(_rigidBody) delete _rigidBody; arg->setUserPointer(this); _rigidBody = arg; }
        inline btRigidBody*
            getRidgidBody() const { return _rigidBody; }


    protected:

    private:
        ModelAsset _asset;
        Patronus::Mesh * _meshPtr;
        std::string _id;
        btRigidBody * _rigidBody;



    };
}

#endif // INSTANCE_H
