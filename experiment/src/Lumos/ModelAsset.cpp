#include "GL_include.h"
#include "ModelAsset.h"

#include "Extern.h"


using namespace Lumos;


GLenum Material::getBitmapFormat()
{

}


void Material::loadUniforms() const{

    GLuint uniformId;
    if (gProgram->hasUniform("tex")){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, glTexId);
        gProgram->setUniform("tex", 0);
        //set to 0 because the texture is bound to GL_TEXTURE0
    }
    if (gProgram->hasUniform("transmittance")){
        gProgram->setUniform("transmittance", transmittance);
    }
    if (gProgram->hasUniform("hasTexture")){
        gProgram->setUniform("hasTexture", !texture.isNull());
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
