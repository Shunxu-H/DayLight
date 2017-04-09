#ifndef MOUSE_H
	#define MOUSE_H

//#include "OrthoView.h"
#include "Vector.h"

class View;

class OrthoView;
class Mouse{
public:
	Mouse();
	Mouse( View* _v);
	~Mouse(){} ;

	void mouseHold(int x, int y);
	void mouseClick(int button, int state, int x, int y);
	void mouseHover(int x, int y);
	void viewClipLine();

	void drawSelectionBox();

protected:


private:
	View* view;
	int curPos[2];
	int prevPos[2];
	void clipUP();
	void clipDOWN();
	void clipLEFT();
	void clipRIGHT();
	Vector selectedArea[2];
	bool isTranslating;
	bool isSelecting;
	bool isAddingVertex;
	bool isRotatingCamera;
	std::shared_ptr<Vector> vertexHolder;
	inline bool sameSign(float a, float b) {return a*b >= 0.0f;};




};



	#endif