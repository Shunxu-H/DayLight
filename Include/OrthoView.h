#ifndef ORTHOVIEW_H
	#define ORTHOVIEW_H

#include <GL/glut.h>
#include <string>
#include <utility>
#include <vector>
#include "Index.h"
#include "Vector.h"
#include "View.h"
#include "Face.h"

class Mouse;
class Keyboard;


class WindowManager;

class OrthoView: public View
{
public:
	OrthoView(){};
	OrthoView(const ViewType &vt, const int& mainContext, const int& loc_x, const int& loc_y, const int& window_width, const int& window_height);//, int canvas_width, int canvas_height);
	~OrthoView();

	void drawLineDDA(Vector v1, Vector v2, const float*);
	void drawLineBSH(const std::shared_ptr<Vector> &v1, const std::shared_ptr<Vector> &v2, float*);

	void updateWindow();

	void reshapeWindow(const Vector& min, const Vector& max);
	void drawAxis();
	void fillPolygon(Geometry &geo);
	void halfToning(Geometry &geometries);
	void fillPolygons(std::vector<std::shared_ptr<Geometry>> &geo);
	INDEX getDeptAxis()const;

	void drawVertex(const Vector & v, float const* color);


	Vector translateFromWorldToViewPort(Vector v)const;

	friend Mouse;

protected:

	INDEX axis1;
	INDEX axis2;
private:
	friend class WindowManager;



	std::shared_ptr<Vector> getMagePixel(const Vector& c);

	void setMagaPix(std::shared_ptr<Vector> magaPix, const int& x, const int& y);


	void drawOutline(const Face & face, const float * color);

	// 1 unit in coordinate lengthes 'coor2pixel' pixel in OrthoView;
};



#endif 