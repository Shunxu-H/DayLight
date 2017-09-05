#ifndef CVM_H
	#define CVM_H

#include <GL/glut.h>
#include <string>
#include <utility>
#include <vector>
#include <QWidget>
#include "Index.h"
#include "Vector.h"
#include "View.h"
#include "Face.h"




class WindowManager;

class CVM: public View
{
public:
    CVM(QWidget *parent);
    CVM(const Patronus::CameraType &vt, const int& mainContext, const int& loc_x, const int& loc_y, const int& window_width, const int& window_height);//, int canvas_width, int canvas_height);
    virtual ~CVM(){}
/*
	void drawLineDDA(Vector v1, Vector v2, const float*);
    void drawLineBSH(const std::shared_ptr<Vector> &v1,  const std::shared_ptr<Vector> &v2, float*);

	void updateWindow();

	void reshapeWindow(const Vector& min, const Vector& max);
	void drawAxis();
	void fillPolygon(Mesh &geo);
	void halfToning(Mesh &geometries);
	void fillPolygons(std::vector<std::shared_ptr<Mesh>> &geo);

	void drawVertex(const Vector & v, float const* color);

	void translateCamera(Vector v);
	void rotateCamera(Vector v);

	friend Mouse;

	Vector translateFromWorldToViewPort(Vector v)const;
	Vector translateFromViewPortToWorld(Vector v)const;

	void rayTrace();

*/

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();


private:
	friend class WindowManager;

	std::shared_ptr<Vector> getMagePixel(const Vector& c);

    //void setMagaPix(std::shared_ptr<Vector> magaPix, const int& x, const int& y);

    //void drawOutline(const Face & face, const float * color);

	Vector fromPoint;
	Vector atPoint;
	Vector UpVector;
	float verticalViewAngle;
	float horizontalViewAngle;
};



#endif 
