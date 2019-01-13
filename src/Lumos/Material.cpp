#include <Common/Extern.h>

#include <Lumos/Program.h>
#include <Lumos/Material.h>

using namespace Daylight::Lumos;


Material::Material( const cv::Mat & im,
                    const color4 & c,
                    const float & reflexitivity_
              )
        : reflexitivity(reflexitivity_)
        , diffuseColor(c)
        , texture(im)
{

}



void Material::loadUniforms( ) const{

    if (gProgram->hasUniform("tex")){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.getObjId());
        gProgram->setUniform("tex", 0);
        //set to 0 because the texture is bound to GL_TEXTURE0
    }
    gProgram->setUniform("transmittance", transmittance);
    gProgram->setUniform("hasTexture", texture.isInitialized());
    gProgram->setUniform("diffuseColor", diffuseColor );
    gProgram->setUniform("ambient", color3(0.05f, 0.05f, 0.05f) );
    gProgram->setUniform("materialShininess", reflexitivity );
    gProgram->setUniform("materialSpecularColor", specular);

}
