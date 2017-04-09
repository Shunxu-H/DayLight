#include <iostream>
#include <cmath>
#include <cstring>
#include "Vector.h"
#include "OrthoView.h"
#include "WindowManager.h"
#include "Matrix.h"
#include "Index.h"
#include "Config.h"

extern WindowManager *winMan;
extern Config progConfig;

Vector::Vector(const float &_x, const float &_y, const float &_z):Matrix(4, 1){
	data[0][X] = _x;
	data[0][Y] = _y; 
	data[0][Z] = _z;
	data[0][3] = 1;
	// /color = nullptr;
}
	



void Vector::toCOORDS(const float& pixelUnit, const float &w_x, const float& w_y, const float& w_z){
	(*this)[X] = (*this)[X]/pixelUnit + w_x;
	(*this)[Y] = (*this)[Y]/pixelUnit + w_y;
	(*this)[Z] = (*this)[Z]/pixelUnit + w_z;
	//std::cout << x << " " << y << std::endl;
}

void Vector::toPXLPOS(const float& pixelUnit, const float &w_x, const float& w_y, const float& w_z){
	(*this)[X] = ((*this)[X] - w_x)*pixelUnit;
	(*this)[Y] = ((*this)[Y] - w_y)*pixelUnit;
	(*this)[Z] = ((*this)[Z] - w_z)*pixelUnit;	
}

Vector Vector::inCOORDS(const float& pixelUnit, const float &w_x, const float& w_y, const float& w_z)const{
	return Vector((*this)[X]/pixelUnit + w_x, (*this)[Y]/pixelUnit + w_y, (*this)[Z]/pixelUnit + w_z);
}

Vector Vector::inPXLPOS(const float& pixelUnit, const float &w_x, const float& w_y, const float& w_z)const{
	return Vector(((*this)[X] - w_x)*pixelUnit, ((*this)[Y] - w_y)*pixelUnit, ((*this)[Z] - w_z)*pixelUnit);
}


/*
Vector Vector::operator*(const float& n)const{
	float x = (*this)[X] * n;
	float y = (*this)[Y] * n;
	float z = (*this)[Z] * n;
	return Vector(x, y, z);
}


Vector Vector::operator+(const Vector& rhs)const{
	float x = (*this)[X] + rhs.(*this)[X];
	float y = (*this)[Y] + rhs.(*this)[X];
	float z = (*this)[Z] + rhs.(*this)[X];
	return Vector(x, y, z);
}

Vector Vector::operator-(const Vector& rhs)const{
	float x = (*this)[X] - rhs.(*this)[X];
	float y = (*this)[Y] - rhs.(*this)[X];
	float z = (*this)[Z] - rhs.(*this)[X];
	return Vector(x, y, z);
}

*/
std::ostream& operator<< (std::ostream& stream, const Vector& v){
	stream << "X: " << v[X] << "; " << "Y: " << v[Y] << "; " <<  "Z: " << v[Z] << "; ";
	return stream;
}

Vector Vector::cross(const Vector& rhs)const{
	float i = (*this)[1]*rhs[2] - (*this)[2]*rhs[1];
	float j = (*this)[2]*rhs[0] - (*this)[0]*rhs[2];
	float k = (*this)[0]*rhs[1] - (*this)[1]*rhs[0];
	return Vector(i, j, k);
}

double Vector::length()const{
	return sqrt( powf(getX(), 2.0f) + powf(getY(), 2.0f) + powf(getZ(), 2.0f) );
}

Vector Vector::makeUnitVector()const{
	double len = length();

	return Vector(getX()/len, getY()/len , getZ()/len);
}


void Vector::normalize(){
	double len = length();
	(*this)[X] = getX()/len;
	(*this)[Y] = getY()/len;
	(*this)[Z] = getZ()/len;
}

// void Vector::setColor(const float& r , const float& g, const float& b){
// 	color[R] = r;
// 	color[G] = g;
// 	color[B] = b;
// }

// void Vector::setColor(const Vector& c){
// 	color[R] = c[R];
// 	color[G] = c[G];
// 	color[B] = c[B];
//}

// Vector Vector::getColor()const{
// 	return Vector(color[R], color[G], color[B]);
// }

/*
Implement this please
*/


void Vector::transform(const Matrix& tm)
{

	Matrix m (4, 1);
	//Matrix result;
	m[0][0] = getX();
	m[0][1] = getY();
	m[0][2] = getZ();
	m[0][3] = 1;
	

	Matrix result = tm * m;

	(*this)[X] = result[0][0];
	(*this)[Y] = result[0][1];
	(*this)[Z] = result[0][2];
	
}

void Vector::draw(float const * color)const{
	winMan->drawVertex(*this, color);
}

Vector Vector::operator*(const float& n)const { 
	Vector ret = static_cast<Matrix>(*this) * n; 
	ret[3] = 1;
	return ret; 
}

Vector Vector::operator/(const float& n)const {
	Vector ret = static_cast<Matrix>(*this) / n; 
	ret[3] = 1;
	return ret; 
}

Vector Vector::operator+(const Vector& rhs)const {
	Vector ret = static_cast<Matrix>(*this) + static_cast<Matrix>(rhs); 
	ret[3] = 1;
	return ret;
}

Vector Vector::operator+(const float& n)const {
	Vector ret = static_cast<Matrix>(*this) + n; 
	ret[3] = 1;
	return ret;
}

Vector Vector::operator-(const Vector& rhs)const {
	Vector ret = static_cast<Matrix>(*this) - static_cast<Matrix>(rhs); 
	ret[3] = 1;
	return ret;
}

Vector Vector::operator-(const float& n)const {
	Vector ret = static_cast<Matrix>(*this) - n; 
	ret[3] = 1;
	return ret;
}

Vector Vector::operator-()const {
	Vector ret = -static_cast<Matrix>(*this); 
	ret[3] = 1;
	return ret;
}

Vector Vector::transpose()const {
	return static_cast<Matrix>(*this).transpose(); 
}

float Vector::dot(const Vector& v)const{
	return (*this)[X] * v[X] + (*this)[Y] * v[Y] + (*this)[Z] * v[Z] ; 
};

Vector Vector::getReflectionVector(const Vector & normal)const{
	return (-*this) - (normal*((-*this).dot(normal)*2));
}

Vector Vector::getRefractionVector(const Vector & normal, const float & nRatio)const{
	return Vector();
}

