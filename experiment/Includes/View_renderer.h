#ifndef VIEW_RENDERER_H
#define VIEW_RENDERER_H

#include "View.h"

class View_renderer : public View{
public:
    View_renderer(
        const std::shared_ptr< Patronus::Camera > & cam = std::shared_ptr<Patronus::Camera>( nullptr ),
        const std::string & shaderId = Lumos::Shader::default_mesh_shader_id
         );


protected:
    virtual void paintGL() override;
    virtual void initializeGL() override;


private:
    bool _isReadyToRender;
};

#endif // VIEW_RENDERER_H
