#include <cmath>

#include "Vector.h"
#include "Edge.h"




Edge::Edge(const Edge& e){
	if ( e.head != nullptr )
		head = std::shared_ptr<Vector>( new Vector( *e.head ));
	if ( e.tail != nullptr )
		tail = std::shared_ptr<Vector>( new Vector( *e.tail ));
}

void Edge::makeUnitVector(){
	double len = length();
	//*head = (*head)*(1/len);
	
	*tail = *tail - *head;
	*tail = *tail*(1/len);
	*tail = *tail + *head;
}

double Edge::length(){
	return sqrt( pow(tail->getX() - head->getX(), 2) + pow(tail->getY() - head->getY(), 2) + pow(tail->getZ() - head->getZ(), 2) );
}


float Edge::getMaxX()const{
	return std::max(head->getX(), tail->getX());
}

float Edge::getMinX()const{
	return std::min(head->getX(), tail->getX());
}

float Edge::getMaxY()const{
	return std::max(head->getY(), tail->getY());
}

float Edge::getMinY()const{
	return std::min(head->getY(), tail->getY());
}

float Edge::getMaxZ()const{
	return std::max(head->getZ(), tail->getZ());
}

float Edge::getMinZ()const{
	return std::min(head->getZ(), tail->getZ());
}

/* implement this please*/
std::string Edge::save()const{ 
	return std::string();
}

void Edge::clear(){

}

void Edge::transform(const Matrix & m){

}

void Edge::draw(float const *color)const{

}

std::ostream& operator<< (std::ostream& stream, const Edge & edge){ 
	return stream; 
};

