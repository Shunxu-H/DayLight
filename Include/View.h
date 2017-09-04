#ifndef VIEW_H
	#define VIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <memory>
#include "Camera.h"

class WindowManager;

class View: public QOpenGLWidget
{
    Q_OBJECT
public:
    View(){}
    View(
            QWidget *parent = nullptr,
            const std::shared_ptr< Patronus::Camera > & cam = std::shared_ptr<Patronus::Camera>( nullptr )
         );

    //View(const Patronus::CameraType &vt, const int& mainContext, const int& loc_x, const int& loc_y, const int& window_width, const int& window_height);//, int canvas_width, int canvas_height);
    virtual ~View(){}

    inline void
        setCamInUse( const std::shared_ptr<Patronus::Camera> & cam) { _camInUse = cam; }
    inline std::shared_ptr<Patronus::Camera>
        getCamInUse() const { return _camInUse; }

protected:

    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;



private:
    friend class WindowManager;
    std::shared_ptr<Patronus::Camera> _camInUse;

};



#endif 
