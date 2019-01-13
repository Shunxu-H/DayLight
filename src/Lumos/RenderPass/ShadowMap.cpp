#include <glm/gtc/matrix_transform.hpp>

#include <Common/Extern.h>

#include <Patronus/PhysicalWorld.h>
#include <Patronus/Shaper.h>

#include <Lumos/RenderPass/ShadowMap.h>
#include <Lumos/Program.h>



using namespace Daylight::Lumos; 

void ShadowMap::configureShaderAndLoadResources(){
        
} 

void ShadowMap::render(){


    // 0. Clear color
    glClearColor(0, 0, 0, 1); // black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gProgram->use();
    glViewport(0, 0, getWidth(), getHeight());
    gProgram->enableShadingPipe(_shadingPipeId);
    _depthTexBuffer.use(); 

    // 1. render depth of scene to texture (from light's perspective)
    // --------------------------------------------------------------
    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
    float near_plane = 1.0f, far_plane = 7.5f;
    lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    lightSpaceMatrix = lightProjection * lightView;
    // render scene from light's point of view
    gProgram->setUniform("lightSpaceMatrix", lightSpaceMatrix);

    // _camInUse->loadUniforms(_width, _height);
    shaper->loadAttribsAndUniform();
    Lumos::Material * materialInUse = nullptr;
    Utils::logOpenGLError( std::string(__FUNCTION__) + ":" + std::to_string(__LINE__) );
    for(Lumos::Instance const * i : world->getInstances()){
        if (i->isVisible())
            i->renderMesh(materialInUse);
    }

    gProgram->disableShadingPipe(_shadingPipeId);
    

}
