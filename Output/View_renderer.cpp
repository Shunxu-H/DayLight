#include "View_renderer.h"
#include "Extern.h"


View_renderer::View_renderer(  QWidget *parent, const std::shared_ptr< Patronus::Camera > & cam)
    :View(parent, cam)
{

}

void View_renderer::mousePressEvent(QMouseEvent *event){

}

void View_renderer::mouseMoveEvent(QMouseEvent *event){

}

void View_renderer::mouseReleaseEvent(QMouseEvent *event){

}

void View_renderer::wheelEvent ( QWheelEvent * event ) {

}
/*
void View_renderer::paintGL(){
    if( gProgram == nullptr )
        return;
    glClearColor(0, 0, 0, 1); // black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gProgram->use();
    glBindVertexArray(_VAO);

    gProgram->enableShadingPipe(Lumos::Shader::default_mesh_shader_id);

    _camInUse->loadUniforms(width(), height());
    shaper->loadAttribsAndUniform();

    Lumos::Material * materialInUse = nullptr;
    for(Lumos::Instance const * i : world->getInstances()){
        i->renderMesh(materialInUse);
    }

    gProgram->disableShadingPipe(Lumos::Shader::default_mesh_shader_id);
}
*/
