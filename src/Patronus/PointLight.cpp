
#include <Common/GL_include.h>
#include <Common/Extern.h>

#include <Lumos/Program.h>

#include <Patronus/PointLight.h>



using namespace Daylight::Patronus; 

void PointLight::setUniformsAndAttributes(void * data){

    int i = *static_cast<int*>(data); 
    gProgram->SetLightUniform("isDirectional", i, getLightType() == LIGHT_DIRECTIONAL);
    gProgram->SetLightUniform("position", i, getTranslatev4());
    gProgram->SetLightUniform("intensities", i, getIntensity());
    gProgram->SetLightUniform("attenuation", i, getAttenuation());
    gProgram->SetLightUniform("ambientCoefficient", i, getAmbientCoefficient());
    gProgram->SetLightUniform("coneAngle", i, getConeAngle());
    gProgram->SetLightUniform("coneDirection", i, getConeDirection());
}
