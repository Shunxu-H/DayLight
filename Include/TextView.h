#ifndef TEXTVIEW_H
	#define TEXTVIEW_H

#include "View.h"

class WindowManager;
class TextView: public View{
public:
	TextView(const ViewType &vt, const int& mainContext, const int& loc_x, const int& loc_y, const int& window_width, const int& window_height);
	void drawLineDDA(Vector v1, Vector v2, const float* color);
	void drawAxis();


	Vector translateFromWorldToViewPort(Vector v)const{};

protected:

private:
	friend class WindowManager;
	void updateWindow();
};



	#endif 