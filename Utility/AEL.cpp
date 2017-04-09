#include <iostream>
#include "AEL.h"

float AEL::next(){
	if (!isActivated){
		isActivated = true;

	} 
	else{
		x += dx;
	}
	return x;
}

void AEL::print(){
	std::cout << "X: " << x << "; " << "Y: " << y << std::endl;
}