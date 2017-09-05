#ifndef COLOR_H
	#define COLOR_H

#include "GL_include.h"
#include "Index.h"

class Color
{
public:
	Color();



    const static color4 BLACK ;
    const static color4 DGREY ;
    const static color4 GREY  ;
    const static color4 LGREY ;
    const static color4 WHITE ;
    const static color4 RED   ;
    const static color4 GREEN ;
    const static color4 DGREEN;
    const static color4 BLUE  ;

	float* getColor(const float&,const float&, const float&);
	void print (float*);


protected:

private:
};


    #endif
