
#include <Common/GL_include.h>
#include <Common/Extern.h>

#include <Lumos/GlslNameConst.h>
#include <Lumos/Program.h>

#include <Patronus/Shaper.h>
#include <Patronus/DirectionalLight.h>

#include <glm/gtc/matrix_transform.hpp>

using namespace Daylight; 
using namespace Daylight::Patronus; 


void DirectionalLight::setUniformsAndAttributes(void * data){
    
    // render scene from light's point of view
    gProgram->setUniform(GLSL_LIGHTSPACE_MATRIX, getLightSpaceMatrix());

    
    // for multilight shader
    int i = *static_cast<int*>(data); 
    gProgram->SetLightUniform("isDirectional", i, getLightType() == LIGHT_DIRECTIONAL);
    gProgram->SetLightUniform("position", i, getTranslatev4());
    gProgram->SetLightUniform("intensities", i, getIntensity());
    gProgram->SetLightUniform("attenuation", i, getAttenuation());
    gProgram->SetLightUniform("ambientCoefficient", i, getAmbientCoefficient());
}


glm::mat4 DirectionalLight::getLightSpaceMatrix() const{
    point3 center; 
    float radius; 
    shaper->getBoundingSphere(Daylight::Patronus::Shaper::global_vertices, &center, &radius); 
    float near_plane = 1.0f, far_plane = 2.0f * radius;
    glm::mat4 lightProjection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, near_plane, far_plane);

    glm::mat4 lightView = glm::lookAt( center + (getOrientation() * radius), center, glm::vec3( 0.0f, 1.0f,  0.0f));
    return  lightProjection * lightView;
}