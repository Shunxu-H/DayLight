#ifndef VIEW_RENDERER_H
#define VIEW_RENDERER_H

#include "View.h"

class View_renderer : public View{
public:
    View_renderer(
    		const size_t & w = 500,
    		const size_t & h = 500,
	        const std::shared_ptr< Patronus::Camera > & cam = std::shared_ptr<Patronus::Camera>( nullptr ),
	        const std::string & shaderId = Lumos::Shader::default_mesh_shader_id
         );
    virtual ~View_renderer();

    void toImageFile_color( const std::string & fileName );
    void toImageFile_depth( const std::string & fileName );
    void getVisibleObjects();
    void generateMasks();
    void generateData();

    virtual void initializeGL() override;
    virtual void resizeGL(const size_t & w, const size_t &h) override;
    
protected:


private:
    GLuint _FBO;
    GLuint _ColorTextureObject;
    GLuint _DepthTextureObject;
    GLuint _ColorBuffer;
    GLuint _DepthBuffer;

    void _saveColorTexture(const std::string & fileName);
    void _saveDepthTexture(const std::string & fileName);
    void _deleteTextures();
    void _remakeTextureObjects();
    void _deleteBuffers();
    void _remakeBuffers();
    void _getColorAndDepthTexture();
    void _getColorAndDepthBuffers();
};

#endif // VIEW_RENDERER_H
