#include <cmath>
#include "Line.h"
#include "Ellipsoid.h"
#include "WindowManager.h"
#include "Shader.h"
#include "Config.h"

extern WindowManager* winMan;
extern Shader* shader;
extern Config progConfig;


Ellipsoid::Ellipsoid(const Vector & _center, const Vector & _offset):Object(ELLIPSOID){
	center = _center;
	offset = _offset;
}


void Ellipsoid::transform(const Matrix & m){
	center = m*center;
}

void Ellipsoid::draw(float const*c)const{
	center.draw(c);
}

std::shared_ptr<Vector> Ellipsoid::getIntersection(const Line & line)const{
	float t = 0;

	// get M 
	Matrix M (4, 0);
	M.concatenate(Vector(1/offset[X], 0, 0));
	M.concatenate(Vector(0, 1/offset[Y], 0));
	M.concatenate(Vector(0, 0, 1/offset[X]));
	M.concatenate(Vector(0, 0, 0));
	M[0][3] = 0;
	M[1][3] = 0;
	M[2][3] = 0;
	M[3][3] = 1;

	// 
	Vector v1 = M*line.getVelocity();
	Vector p1 = (M*line.getOrigin()) - (M*center);
	float a = pow(v1.length(), 2.0);
	float b = 2*(p1.dot(v1));
	float c = pow(p1.length(), 2.0) - 1;
	if (pow(b, 2.0) - 4*a*c < 0)
		return std::shared_ptr<Vector>(nullptr);

	float t1 = (-b + sqrt(pow(b, 2.0) - 4*a*c)) / (2*a);
	float t2 = (-b - sqrt(pow(b, 2.0) - 4*a*c)) / (2*a);


	if ( t1 <= 0.00001 || t2 <= 0.00001)
		return std::shared_ptr<Vector>(nullptr);

	Vector ret1 = line.getOrigin() + (line.getVelocity()*t1);
	Vector ret2 = line.getOrigin() + (line.getVelocity()*t2);
	
	return std::make_shared<Vector> (((ret1 - line.getOrigin()).length() < (ret2 - line.getOrigin()).length())? ret1 : ret2);
}

Vector Ellipsoid::getNormal(const Vector & v)const{
	return Vector(2*(v[X]-center[X])/pow(offset[X], 2.0f),2*(v[Y]-center[Y])/pow(offset[Y], 2.0f),2*(v[Z]-center[Z])/pow(offset[Z], 2.0f) );
}


std::string Ellipsoid::save()const{
	std::string str="";
	// dump type
	str.append(std::to_string(type) + " ");
	// dumping vertexes
	str.append(std::to_string(color[R]) + " " + std::to_string(color[G]) + " " + std::to_string(color[B]) + "\n");

	str.append(std::to_string(center[X]) + " " + std::to_string(center[Y]) + " " + std::to_string(center[Z]) + " \n");
	str.append(std::to_string(offset[X]) + " " + std::to_string(offset[Y]) + " " + std::to_string(offset[Z]) + " \n");

	str.append(" \n");


	return str;
}