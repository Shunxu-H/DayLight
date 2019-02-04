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



void Material::loadUniforms(Program program) const{

    if (program.hasUniform("tex")){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.getObjId());
        program.setUniform("tex", 0);
        //set to 0 because the texture is bound to GL_TEXTURE0
    }
    program.setUniform("transmittance", transmittance);
    program.setUniform("hasTexture", texture.isInitialized());
    program.setUniform("diffuseColor", diffuseColor );
    program.setUniform("ambient", color3(0.05f, 0.05f, 0.05f) );
    program.setUniform("materialShininess", reflexitivity );
    program.setUniform("materialSpecularColor", specular);

}
