#include <glm/gtc/matrix_transform.hpp>

#include <Common/Extern.h>
#include <Common/Utility.h>

#include <Patronus/PhysicalWorld.h>
#include <Patronus/Shaper.h>

#include <Lumos/RenderPass/ShadowMap.h>
#include <Lumos/Program.h>



using namespace Daylight::Lumos; 

ShadowMap::ShadowMap(const size_t & width, const size_t & height) 
: _frameBuffer(width, height)
, _shadingPipeId("DepthMap")
, _program(){

                
}

void ShadowMap::configureShaderAndLoadResources(){

    

} 

void ShadowMap::render(){


    // _frameBuffer.use(); 
    glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer.getObjId());
    // 0. Clear color

    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    _program.bind();
    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    _program.enableShadingPipe(_shadingPipeId);

    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    _program.use();

    GLError( __PRETTY_FUNCTION__ , __LINE__ );

    glClearColor(0, 0, 0, 1); // black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, getWidth(), getHeight());

    GLError( __PRETTY_FUNCTION__ , __LINE__ );

    GLError( __PRETTY_FUNCTION__ , __LINE__ );

    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    // _frameBuffer.getDepthTexBuffer().use(); 
    // _frameBuffer.getColorTexBuffer().use(); 

    // 1. render depth of scene to texture (from light's perspective)
    // --------------------------------------------------------------
    // glm::mat4 lightProjection, lightView;
    // glm::mat4 lightSpaceMatrix;


    // float near_plane = 1.0f, far_plane = 75.0f;5
    // lightProjection = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, near_plane, far_plane);
    // glm::vec3 lightPos(-20.0f, 40.0f, -10.0f);
    // lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    // lightSpaceMatrix = lightProjection * lightView;
    // // render scene from light's point of view
    // gProgram->setUniform("lightSpaceMatrix", lightSpaceMatrix);

    // _camInUse->loadUniforms(_width, _height);
    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    shaper->loadAttribsAndUniform(_program);
    Lumos::Material * materialInUse = nullptr;
    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    for(Lumos::Instance const * i : world->getInstances()){
        if (i->isVisible())
            i->renderMesh(_program, materialInUse);
    }

    // _frameBuffer.saveDepthBuffer2file("DepthMap.png"); 
    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    _program.disableShadingPipe(_shadingPipeId);

    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    _program.stopUsing();

    // _frameBuffer.saveDepthBuffer2file("DepthMap.png");
    // _frameBuffer.stopUsing();
    glBindFramebuffer(GL_FRAMEBUFFER, 0); 
    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    // _frameBuffer.stopUsing(); 

    // glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    

}
