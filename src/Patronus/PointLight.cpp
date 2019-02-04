
#include <Common/GL_include.h>
#include <Common/Extern.h>

#include <Lumos/Program.h>

#include <Patronus/PointLight.h>



using namespace Daylight::Patronus; 

void PointLight::setUniformsAndAttributes(Lumos::Program program, void * data){

    int i = *static_cast<int*>(data); 
    program.SetLightUniform("isDirectional", i, getLightType() == LIGHT_DIRECTIONAL);
    program.SetLightUniform("position", i, getTranslatev4());
    program.SetLightUniform("intensities", i, getIntensity());
    program.SetLightUniform("attenuation", i, getAttenuation());
    program.SetLightUniform("ambientCoefficient", i, getAmbientCoefficient());
    program.SetLightUniform("coneAngle", i, getConeAngle());
    program.SetLightUniform("coneDirection", i, getConeDirection());
}
