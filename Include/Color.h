#ifndef COLOR_H
	#define COLOR_H


#include "Index.h"

class Color
{
public:
	Color();

	float BLACK[4];
	float LGREY[4];
	float GREY[4];
	float DGREY[4];
	float WHITE[4];
	float RED[4];
	float GREEN[4];
	float DGREEN[4];
	float BLUE[4];

	float* getColor(const float&,const float&, const float&);
	void print (float*);


protected:

private:
};


	#endif