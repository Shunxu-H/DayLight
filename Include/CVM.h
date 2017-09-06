#ifndef CVM_H
	#define CVM_H

#include <GL/glut.h>
#include <string>
#include <utility>
#include <vector>
#include <QWidget>
#include "View.h"
#include "Camera.h"


class WindowManager;

class CVM: public View
{
public:
    CVM(QWidget *parent);
    CVM(const Patronus::CameraType &vt, const int& mainContext, const int& loc_x, const int& loc_y, const int& window_width, const int& window_height);//, int canvas_width, int canvas_height);
    virtual ~CVM(){}


protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();


private:


};



#endif 
