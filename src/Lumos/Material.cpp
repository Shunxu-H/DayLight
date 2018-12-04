#include "Material.h"
#include "Common/Extern.h"

#include "Lumos/Program.h"

using namespace Lumos;


Material::Material( const cv::Mat & im,
                    const color4 & c,
                    const float & reflexitivity_
              )
        : reflexitivity(reflexitivity_)
        , diffuseColor(c)
        , texture(im)
{

}



void Material::loadUniforms( Program * program ) const{

    if (program->hasUniform("tex")){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.getObjId());
        program->setUniform("tex", 0);
        //set to 0 because the texture is bound to GL_TEXTURE0
    }
    if (program->hasUniform("transmittance")){
        program->setUniform("transmittance", transmittance);
    }
    if (program->hasUniform("hasTexture")){
        program->setUniform("hasTexture", texture.isInitialized());
    }
    if (program->hasUniform("diffuseColor"))
        program->setUniform("diffuseColor", diffuseColor );

    if (program->hasUniform("ambient"))
        program->setUniform("ambient", color3(0.05f, 0.05f, 0.05f) );

    if (program->hasUniform("materialShininess"))
        program->setUniform("materialShininess", reflexitivity );

    if (program->hasUniform("materialSpecularColor"))
        program->setUniform("materialSpecularColor", specular);

}
