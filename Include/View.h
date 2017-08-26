#ifndef VIEW_H
	#define VIEW_H

#include <GL/glut.h>
#include <string>
#include <utility>
#include <vector>


#include <memory>
#include "Index.h"
#include "Vector.h"
#include "AEL.h"

class Mouse;
class Keyboard;
class Face;

class WindowManager;

enum ViewType
{
	XY, 
	ZY,
	XZ,
	CABINET,
	PERSP,
	TEXTVIEW

};


class View
{
public:
	View(){};
	View(const ViewType &vt, const int& mainContext, const int& loc_x, const int& loc_y, const int& window_width, const int& window_height);//, int canvas_width, int canvas_height);
	~View();

	inline bool isOrthoView()const{ return viewType == XY || viewType == XZ || viewType == ZY;}
	inline bool isCVM()const {return viewType == PERSP; }

//view->getPixelPerUnit(), view->getX(), view->getY(), view->getZ()
	inline void toCOORDS(Vector & v)const{v.toCOORDS(pixelsPerUnit, coordLoc[X], coordLoc[Y], coordLoc[Z]);};
	inline void toPXLPOS(Vector & v)const{v.toPXLPOS(pixelsPerUnit, coordLoc[X], coordLoc[Y], coordLoc[Z]);};
	
	inline Vector returnCOORDS(const Vector & v)const{return v.inCOORDS(pixelsPerUnit, coordLoc[X], coordLoc[Y], coordLoc[Z]);};
	inline Vector returnPXLPOS(const Vector & v)const{return v.inPXLPOS(pixelsPerUnit, coordLoc[X], coordLoc[Y], coordLoc[Z]);};

	virtual void fillPolygon(Geometry &geo, const float *);
	virtual void fillPolygons(std::vector<std::shared_ptr<Geometry>> &geo){}
	
	virtual void halfToning(Geometry &geometries);
	void drawLineBSH(const std::shared_ptr<Vector> &v1, const std::shared_ptr<Vector> &v2, float*);
	virtual void drawLineDDA(Vector v1, Vector v2, const float*) = 0;
	virtual void drawAxis() = 0;
	void drawLine( const std::vector<Vector> &vertexBuffer, const float*);
	void drawHorizontal(const int &y, const float* =nullptr);
	void drawVertical(const int &x, const float* =nullptr);

	void drawHorizontal(const int &y, const int &x1, const int &x2, const float* =nullptr);
	void drawVertical(const int &x,const int &y1, const int &y2, const float* =nullptr);

	void setPix(const Vector*, const float*);
	void setPix(const int&, const int&, const float*);
	void clear();

	virtual void updateWindow() = 0;
	void drawOutline();
	void drawVertex(const Vector & v);
	void drawLines(const std::vector<std::shared_ptr<Vector>> &line)const;

	inline int getHeight()const { return width; };
	inline int getWidth()const { return height; };
	inline float* getBuffer()const { return PixelBuffer.get(); };

	inline float getX()const { return coordLoc[X]; };
	inline float getY()const { return coordLoc[Y]; };
	inline float getZ()const { return coordLoc[Z]; };
	inline float getPixelPerUnit()const { return pixelsPerUnit; };
	void mouseClick(const int& button, const int& state, const int& x, const int& y);
	void mouseHold(int x, int y);
	void mouseHover(int x, int y);

	void keyboardHandler(unsigned char key, int x, int y);
	void keyboardReleaseHandler(unsigned char key, int x, int y);

	//void reshapeWindow(const Vector& min, const Vector& max);

	friend Mouse;

	void drawRect(const float & xMin, const float & yMin, const float & xMax, const float & yMax, float const*);

	inline int getWindowContext(){ return windowContext; }
	inline void setWindowContext(const int & id){ windowContext = id;}
	inline ViewType getType()const { return viewType;}
	inline ViewType setType(const ViewType _type){ viewType = _type;}


	void drawVertex(const Vector & v, float const* color);

	virtual Vector translateFromWorldToViewPort(Vector v)const=0;

protected:

	std::unique_ptr<float> PixelBuffer;

	ViewType viewType;
	int windPos[2]; // coordinate of the current window w.r.t the main window
	float coordLoc[3];
	int windowContext;
	float pixelsPerUnit; 
	float width, height;
	static Keyboard keyboard; 
	void drawLineDDA(float x1, float y1, float x2, float y2, float const* color);
	Vector interpolate(const float& startPr, const float& endPr, const float& x, const Vector &startColor, const Vector &endColor)const;
	Mouse *mouse;

private:
	friend class WindowManager;

	void init();
	// 1 unit in coordinate lengthes 'coor2pixel' pixel in OrthoView;
};



#endif 
