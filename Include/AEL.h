#ifndef AEL_H
	#define AEL_H
#include <memory>
#include "Vector.h"
class AEL
{
public:
	AEL(const float &_x, const float &_y, const float &_dx, const int &_lY, Vector c1, Vector c2):
		x(static_cast<int>(_x)), y(static_cast<int>(_y)), dx(_dx), lastY(static_cast<int>(_lY)), color1(c1), color2(c2){ isActivated = false; };
	float next();
	inline float getY()const{ return y; }
	inline float getLastY()const{ return lastY; }
	inline bool hasEnded(const int& curLine)const{ return lastY > curLine - 1; };
	inline void activate() {isActivated = true; };
	inline Vector getC1()const{ return color1; }
	inline Vector getC2()const{ return color2; }
	void print();
private:
	bool isActivated;
	float x;
	float y;
	float dx;
	float lastY;
	Vector color1;
	Vector color2;
};



	#endif