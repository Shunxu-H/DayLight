#include <cstring>
#include <iostream>
#include "Color.h"


const color4 Color::BLACK  = color4{ 0.00f,  0.00f,  0.00f, 1.00f };
const color4 Color::DGREY  = color4{ 0.25f,  0.25f,  0.25f, 1.00f };
const color4 Color::GREY   = color4{ 0.50f,  0.50f,  0.50f, 1.00f };
const color4 Color::LGREY  = color4{ 0.80f,  0.80f,  0.80f, 1.00f };
const color4 Color::WHITE  = color4{ 1.00f,  1.00f,  1.00f, 1.00f };
const color4 Color::RED    = color4{ 1.00f,  0.00f,  0.00f, 1.00f };
const color4 Color::GREEN  = color4{ 0.00f,  1.00f,  0.00f, 1.00f };
const color4 Color::DGREEN = color4{ 0.00f,  0.50f,  0.00f, 1.00f };
const color4 Color::BLUE   = color4{ 0.00f,  0.00f,  1.00f, 1.00f };



int Color::toUniqueInt( const int & r, const int & g, const int & b ){
    int pickedID =
        r +
        g * 256 +
        b * 256*256;
    return pickedID;
}

color3 Color::toUniqueColor ( const int & i){
    int r = (i & 0x000000FF) >>  0;
    int g = (i & 0x0000FF00) >>  8;
    int b = (i & 0x00FF0000) >> 16;
    return color3( r, g, b);
}

Color::Color(){


}



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

