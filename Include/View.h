#ifndef VIEW_H
	#define VIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QPoint>
#include <memory>
#include "GL_include.h"

class WindowManager;

namespace Patronus {
    class Camera;
}

class View: public QOpenGLWidget
{
    Q_OBJECT
public:
    View(
            QWidget *parent = nullptr,
            const std::shared_ptr< Patronus::Camera > & cam = std::shared_ptr<Patronus::Camera>( nullptr )
         );

    //View(const Patronus::CameraType &vt, const int& mainContext, const int& loc_x, const int& loc_y, const int& window_width, const int& window_height);//, int canvas_width, int canvas_height);
    virtual ~View(){}

    inline void
        setCamInUse( Patronus::Camera * cam) { _camInUse = cam; }
    inline Patronus::Camera*
        getCamInUse() const { return _camInUse; }


    void fitSphere(const point3 & position, const float & radius);
protected:

    virtual void initializeGL() override ;
    virtual void resizeGL(int w, int h) override ;
    virtual void paintGL() override ;

    void getMouseBeam(const int & mouseX, const int & mouseY, point3 * start, point3 * direction )const;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void wheelEvent ( QWheelEvent * event ) override;



private:
    friend class WindowManager;
    Patronus::Camera * _camInUse;
    QPoint _prevMousePos;

};



#endif 
