#include <glm/gtc/matrix_transform.hpp>

#include <Common/GL_include.h>
#include <Common/Extern.h>
#include <Common/Utility.h>

#include <Lumos/GlslNameConst.h>
#include <Lumos/Program.h>

#include <Patronus/Shaper.h>
#include <Patronus/DirectionalLight.h>


using namespace Daylight; 
using namespace Daylight::Patronus; 


void DirectionalLight::setUniformsAndAttributes(Lumos::Program program, void* data){
    
    // render scene from light's point of view
    program.setUniform(GLSL_LIGHTSPACE_MATRIX, getLightSpaceMatrix());

    
    // for multilight shader
    int i = Utils::to<int>(data); 
    program.SetLightUniform("isDirectional", i, getLightType() == LIGHT_DIRECTIONAL);
    program.SetLightUniform("position", i, getTranslatev4());
    program.SetLightUniform("intensities", i, getIntensity());
    program.SetLightUniform("attenuation", i, getAttenuation());
    program.SetLightUniform("ambientCoefficient", i, getAmbientCoefficient());
}


glm::mat4 DirectionalLight::getLightSpaceMatrix() const{
    point3 center; 
    float radius; 
    shaper->getBoundingSphere(Daylight::Patronus::Shaper::global_vertices, &center, &radius); 
    float near_plane = 1.0f, far_plane = 2.0f * radius;
    glm::mat4 lightProjection = glm::ortho(-radius, radius, -radius, radius, near_plane, far_plane);

    glm::mat4 rotateMat = glm::mat4(1);
    rotateMat = glm::rotate(rotateMat, _orientation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    rotateMat = glm::rotate(rotateMat, _orientation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    rotateMat = glm::rotate(rotateMat, _orientation.z, glm::vec3(0.0f, 0.0f, 1.0f));

    glm::vec3 orientVec = glm::vec3(rotateMat * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)); 
    glm::mat4 lightView = glm::lookAt( center + ((orientVec * radius)), center, glm::vec3( 0.0f, 1.0f,  0.0f));
    return  lightProjection * lightView;


    // glm::mat4 lightProjection, lightView;
    // glm::mat4 lightSpaceMatrix;
    // float near_plane = 1.0f, far_plane = 75.0f;
    // lightProjection = glm::ortho(0.0f, 100.0f, 100.0f, 0.0f, near_plane, far_plane);
    // glm::vec3 lightPos(-20.0f, 40.0f, -10.0f);
    // lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    // lightSpaceMatrix = lightProjection * lightView;
    // return lightSpaceMatrix; 

}