#include "Material.h"
#include "Extern.h"

using namespace Lumos;


Material::Material( const color4 & c,
                    const float & reflexitivity_
              )
        : reflexitivity(reflexitivity_), diffuseColor(c)
{

}



void Material::loadUniforms() const{

    if (gProgram->hasUniform("tex")){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.getObjId());
        gProgram->setUniform("tex", 0);
        //set to 0 because the texture is bound to GL_TEXTURE0
    }
    if (gProgram->hasUniform("transmittance")){
        gProgram->setUniform("transmittance", transmittance);
    }
    if (gProgram->hasUniform("hasTexture")){
        gProgram->setUniform("hasTexture", !texture.isInitialized());
    }
    if (gProgram->hasUniform("diffuseColor"))
        gProgram->setUniform("diffuseColor", diffuseColor );

    if (gProgram->hasUniform("ambient"))
        gProgram->setUniform("ambient", color3(0.05f, 0.05f, 0.05f) );

    if (gProgram->hasUniform("materialShininess"))
        gProgram->setUniform("materialShininess", reflexitivity );

    if (gProgram->hasUniform("materialSpecularColor"))
        gProgram->setUniform("materialSpecularColor", specular);

}
