#include <cstring>
#include <iostream>
#include "Color.h"



Color::Color(){

	float _BLACK [] = {0.0f,0.0f,0.0f};
	float _DGREY [] = {0.25f,0.25f,0.25f};
	float _GREY  [] = {0.5f,0.5f,0.5f};
	float _LGREY [] = {0.80f,0.80f,0.80f};
	float _WHITE [] = {1.0f,1.0f,1.0f};
	float _RED   [] = {1.0f,0.0f,0.0f};
	float _GREEN [] = {0.0f,1.0f,0.0f};
	float _DGREEN[] = {0.0f,0.5f,0.0f};
	float _BLUE  [] = {0.0f,0.0f,1.0f};
	memcpy( BLACK, _BLACK, 3*sizeof(float));
	memcpy( DGREY, _DGREY, 3*sizeof(float));
	memcpy( GREY,  _GREY,  3*sizeof(float));
	memcpy( LGREY, _LGREY, 3*sizeof(float));
	memcpy( WHITE, _WHITE, 3*sizeof(float));
	memcpy( RED,   _RED,   3*sizeof(float));
	memcpy( GREEN, _GREEN, 3*sizeof(float));
	memcpy( DGREEN,_DGREEN,3*sizeof(float));
	memcpy( BLUE,  _BLUE,  3*sizeof(float));
};



float* Color::getColor(const float& a, const float& b, const float& c){
	float *ret = new float[3];

	ret[0] = a;
	ret[1] = b;
	ret[3] = c;

	return ret;
}


void Color::print (float* c){
	std::cout << c[0] << " " << c[1] << " " << c[2] << std::endl;
}

