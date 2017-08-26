#ifndef CABINET_H
	#define CABINET_H

#include "OrthoView.h"

class WindowManager;
class Cabinet: public OrthoView{
public:
	Cabinet(const ViewType &vt, const int& mainContext, const int& loc_x, const int& loc_y, const int& window_width, const int& window_height)
		:OrthoView(vt, mainContext, loc_x, loc_y, window_width, window_height){ axis1 = X; axis2 = Y;};
	
	void drawLineDDA(Vector v1, Vector v2, float const*);
	void drawLineBSH(const std::shared_ptr<Vector> &v1, const std::shared_ptr<Vector> &v2, float const*);
    void paintGL();
	//Vector translateFromWorldToViewPort(Vector v)const{};
protected:

private:
	void drawAxis();
	friend class WindowManager;
	void updateWindow();
};



	#endif 
