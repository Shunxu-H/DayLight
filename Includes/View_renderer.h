#ifndef VIEW_RENDERER_H
#define VIEW_RENDERER_H

#include "View.h"

class View_renderer : public View{
public:
    View_renderer(
            const size_t & x = 0,
            const size_t & y = 0,
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
    GLuint _Multisampled_FBO;
    GLuint _Multisampled_ColorBuffer;
    GLuint _Multisampled_DepthBuffer;
    GLuint _out_FBO;
    GLuint _out_ColorTextureObject;
    GLuint _out_DepthTextureObject;

    cv::Mat _saveColorImage(const std::string & fileName);
    cv::Mat _saveDepthImage(const std::string & fileName);
    cv::Mat _saveBitMap(const std::string & fileName);
    
    void _saveColorBuffer(const std::string & fileName);
    void _saveDepthBuffer(const std::string & fileName);
    void _deleteMultisampledBuffers();
    void _deleteOutTextures();
    void _makeMultisampledBuffers();
    void _makeOutTextures();
    void _remakeMultisampledBuffers();
    void _remakeOutTextures();
};

#endif // VIEW_RENDERER_H
