#include <vector>
#include <memory>
#include <algorithm>
#include <climits>
#include "Vector.h"
#include <cmath>
#include "Face.h"
#include "Utility.h"
#include "AEL.h"
#include "Shader.h"
#include "Object.h"

extern Shader* shader;

Face::Face(){

}

Face::Face(const Face& f){
	for(auto v: f.vertices)
		vertices.push_back(std::shared_ptr<Vector>(new Vector(*v)));
}

Face::~Face(){
	
}


void Face::addV(std::shared_ptr<Vector> v){
	vertices.push_back(v);
}


std::shared_ptr<Vector> Face::getV(const unsigned int & index)const{
	if(index >= vertices.size())
		return std::shared_ptr<Vector>(nullptr);
	else 
		return vertices[index];
}


void Face::toPXLPOS(const float& pixelUnit, const float& w_x, const float& w_y, const float& w_z){
	for (auto vertex : vertices)
		vertex->toPXLPOS(pixelUnit, w_x, w_y, w_z);
}

Face Face::inPXLCOORD(const float& pixelUnit, const float& w_x, const float& w_y, const float& w_z)const{
	Face ret(*this);
	ret.toPXLPOS(pixelUnit, w_x, w_y, w_z);
	return ret;
}

std::vector<AEL*> Face::getAELs(const float& pixelUnit, const float& w_x, const float& w_y, const float& w_z, const INDEX& axis1, const INDEX& axis2)const{
	// Face f = inPXLCOORD(pixelUnit, w_x, w_y, w_z);

	// f.vertices.push_back(f.vertices[0]);
	// std::vector<AEL*> ret;
	// for (unsigned int i = 0; i < f.vertices.size() - 1; i++){
	// 	Vector *v1, *v2;
	// 	Vector c1, c2;
	// 	if ( (*f.vertices[i])[axis2] == (*f.vertices[i+1])[axis2])
	// 		continue;
	// 	else if ((*f.vertices[i])[axis2] > (*f.vertices[i+1])[axis2]){
	// 		v1 = f.vertices[i].get();
	// 		v2 = f.vertices[i+1].get();
	// 	} 
	// 	else {
	// 		v1 = f.vertices[i+1].get();
	// 		v2 = f.vertices[i].get();
	// 	}
	// 	// v1 has higher y value

	// 	float x1 = (*v1)[axis1], x2 = (*v2)[axis1], y1 = (*v1)[axis2], y2 = (*v2)[axis2];

	// 	ret.push_back(new AEL(x1, y1, -(x1 - x2)/(y1 - y2), y2 , v2->getColor(), v1->getColor()));


	// }

	// sort(ret.begin(), ret.end(), compare );
	
	// return ret;
}


void Face::print(){
	std::cout << vertices.size() << std::endl;
	for(auto v: vertices)
		std::cout << *v << std::endl;
	std::cout << std::endl;
}



Vector Face::getNormalVector()const{
	return (*vertices[2] - *vertices[0]).cross((*vertices[1] - *vertices[0])).makeUnitVector();
}

Vector Face::getCentroid(){
	float xSum = 0, ySum = 0, zSum = 0;
	for (auto v: vertices){
		xSum += v->getX();
		ySum += v->getY();
		zSum += v->getZ();
	}

	xSum /= vertices.size();
	ySum /= vertices.size();
	zSum /= vertices.size();
	
	return Vector(xSum, ySum, zSum);
}


bool Face::hasVector(const Vector& rhs)const{
	for (auto v:vertices)
		if (*v.get() == rhs)
			return true;

	return false;
}



std::shared_ptr<Vector> Face::getIntersection(const Line & line)const{
	// if it intersect with the plane
	Vector normal = getNormalVector().makeUnitVector();
	float D = normal.dot(*vertices[0]);
	if ( normal.dot(line.getVelocity()) == 0 || (D - normal.dot(line.getOrigin()) == 0))
		return std::shared_ptr<Vector>(nullptr);;
	float t = ( D - normal.dot(line.getOrigin())) / (normal.dot(line.getVelocity()));

	if ( t <= 0.001 )
		return std::shared_ptr<Vector>(nullptr);

	if( std::isnan(t))
		std::cout << " t is nan" << std::endl;

	Vector planeIntersection =  line.getOrigin()+(line.getVelocity()*t);
	//planeIntersection.normal = std::make_shared<Vector>(getNormalVector());
	Vector v1 = (*vertices[0] - planeIntersection).cross((*vertices[1] - planeIntersection)).makeUnitVector();
	Vector v2 = (*vertices[1] - planeIntersection).cross((*vertices[2] - planeIntersection)).makeUnitVector();
	Vector v3 = (*vertices[2] - planeIntersection).cross((*vertices[0] - planeIntersection)).makeUnitVector();

	if (v1 == normal && v2 == normal && v3 == normal)
		return std::make_shared<Vector>( planeIntersection);
	else if (v1 != normal && v2 != normal && v3 != normal)
		return std::make_shared<Vector>( planeIntersection);
	else
		return std::shared_ptr<Vector>(nullptr);

}


std::ostream& operator<< (std::ostream& stream, const Face & f){ 
	return stream; 
}


bool Face::contain(const Vector & point)const{
	Vector normal = getNormalVector();
	if (abs(normal.dot(*vertices[0]) - normal.dot(point)) < 0.001)
		return false;
	Vector v1 = (*vertices[0] - point).cross((*vertices[1] - point)).makeUnitVector();
	Vector v2 = (*vertices[1] - point).cross((*vertices[2] - point)).makeUnitVector();
	Vector v3 = (*vertices[2] - point).cross((*vertices[0] - point)).makeUnitVector();

	if (v1 == normal && v2 == normal && v3 == normal)
		return true;
	else if (v1 != normal && v2 != normal && v3 != normal)
		return true;
	else
		return false;
}

float Face::getDistance(const Vector & point)const{
	Vector a = getNormalVector();
	Vector b = point - *vertices[0];
	return fabs(a.dot(b)/a.length());
}