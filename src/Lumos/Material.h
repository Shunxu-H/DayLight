#pragma once

#include "Texture2D.h"

namespace Daylight::Lumos {
    class Program; 
    struct Material{
        float reflexitivity;
        std::string id;
        color3 transmittance;
        color3 specular;
        color4 diffuseColor;
        Texture2D texture;
        Material( const cv::Mat & im = cv::Mat(),
                  const color4 & c = color4(1.0f, 1.0f, 1.0f, 1.0f),
                  const float & reflexitivity_ = 0.3
                );
        ~Material(){

        }
        inline bool hasTexture() const { return !texture.isInitialized();}
        void loadUniforms() const;

    };



}
