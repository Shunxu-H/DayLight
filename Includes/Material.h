#ifndef MATERIAL_H
  #define MATERIAL_H

#include "Texture.h"

namespace Lumos {
    struct Material{
        float reflexitivity;
        std::string id;
        color3 transmittance;
        color3 specular;
        color4 diffuseColor;
        Texture texture;
        Material( const color4 & c = color4(1.0f, 1.0f, 1.0f, 1.0f),
                  const float & reflexitivity_ = 0.3
                );
        ~Material(){

        }
        inline bool hasTexture() const { return !texture.isEmpty();}
        void loadUniforms() const;

    };



}

#endif // MATERIAL_H
