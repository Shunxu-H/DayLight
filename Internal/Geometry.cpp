/*
TO DO:

1. forbid translation to PXLCOORD
*/
#include <cstddef>
#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <memory>
#include <limits>
#include "Geometry.h"
#include "Config.h"
#include "AEL.h"
#include "Shader.h"
#include "Matrix.h"
#include "WindowManager.h"
#include "Edge.h"
#include "Face.h"
#include "Object.h"
//extern OrthoView* OrthoView;
extern WindowManager* winMan;
extern Shader* shader;
extern Config progConfig;



Geometry::Geometry():Object(POLYHEDRON){
	centroid = Vector();
	unitType = COORDS;
}

Geometry::Geometry(const Geometry& geo):Object(POLYHEDRON){

	unitType = geo.unitType;
	centroid = geo.centroid;
	
	for (auto v: geo.vertices)
		vertices.push_back(std::shared_ptr<Vector>(new Vector(*v.get())));

}


Geometry::~Geometry(){
}

int Geometry::getID()const{
	return shader->geoGetN(this);
	
}


Vector Geometry::getCentroid()const{
	return centroid;
}

void Geometry::updateCentroid(){

	float xSum = 0;
	float ySum = 0;
	float zSum = 0;

	for ( auto v: vertices){
		xSum += v->getX();
		ySum += v->getY();
		zSum += v->getZ();
	}
	std::cout << "centroid: " << xSum << " "  << ySum << " "  << zSum <<std::endl;  
	//if ( sqrt( pow( ret.getX() - centroid.getX() , 2) + pow( ret.getY() - centroid.getY() , 2) ) > 1) 
		//centroid = ret;
	centroid = Vector(xSum / static_cast<float>(size()), ySum / static_cast<float>(size()), zSum / static_cast<float>(size()));

}

void Geometry::transform(const Matrix& tm){
	// construct matri
	Matrix m (4, size());
	//Matrix result;
	for (unsigned int vCnt = 0; vCnt < size(); vCnt++){
		m[vCnt][0] = vertices[vCnt]->getX();
		m[vCnt][1] = vertices[vCnt]->getY();
		m[vCnt][2] = vertices[vCnt]->getZ();
		m[vCnt][3] = 1;
	}
	Matrix result = tm * m;

	for (unsigned int vCnt = 0; vCnt < size(); vCnt++){
		vertices[vCnt]->setX(result[vCnt][0]);
		vertices[vCnt]->setY(result[vCnt][1]);
		vertices[vCnt]->setZ(result[vCnt][2]);
	}

}

void Geometry::operator+=(std::shared_ptr<Vector> v)
{
	vertices.push_back( v );

}


void Geometry::operator+=(std::shared_ptr<Edge> e){
	edges.push_back( e );
}


void Geometry::operator+=(std::shared_ptr<Face> f){
	faces.push_back( f );
}

void Geometry::clear(){
	vertices.clear();
	edges.clear();
}


/*
*/
void Geometry::toPXLPOS(const float& pixelUnit, const float& w_x, const float& w_y, const float& w_z){
	if(isType(PXLPOS))
		return;
	
	unitType = PXLPOS;
	for (auto vertex : vertices)
		vertex->toPXLPOS(pixelUnit, w_x, w_y, w_z);
}


std::string Geometry::save()const{	
	std::string str="";

	// dump type
	str.append(std::to_string(type) + " ");

	// dumping vertexes
	str.append(std::to_string(color[R]) + " " + std::to_string(color[G]) + " " + std::to_string(color[B]) + "\n");


	str.append(std::to_string(size()) + "\n" );
	for (auto vertex : vertices){
		str.append(std::to_string(vertex->getX()) + " " );
		str.append(std::to_string(vertex->getY()) + " " );
		str.append(std::to_string(vertex->getZ()) + "\n" );
	}
	str.append("\n" );

	// dumping edges 
	str.append(std::to_string(edges.size()) + "\n" );
	for (auto edge : edges){
		str.append(std::to_string(vGetN(*edge->getHead())) + " " );
		str.append(std::to_string(vGetN(*edge->getTail())) + "\n" );
	}
	str.append("\n" );

	// dumping faces 
	str.append(std::to_string(faces.size()) + "\n" );
	for (auto face : faces){
		str.append(std::to_string(vGetN(*face->getV(0))) + " " );
		str.append(std::to_string(vGetN(*face->getV(1))) + " " );
		str.append(std::to_string(vGetN(*face->getV(2))) + "\n" );
	}
	str.append("\n" );

	return str;
}

int Geometry::vGetN(const Vector &v)const{
	for ( unsigned int i = 0; i < vertices.size(); i++ )
		if ( v == *vertices[i].get() )
			return i;

	return -1;
}


std::shared_ptr<Vector> Geometry::nGetV(const unsigned int& index){
	if (index >= vertices.size())
		return std::shared_ptr<Vector>(nullptr);
	else
		return vertices[index];
}

void Geometry::draw(float const* color)const
{
	drawLines(color);
}

void Geometry::drawNormal()const{

	for (auto face: faces){
		winMan->drawLine(face->getCentroid(), 
						static_cast<Vector>(face->getCentroid() + face->getNormalVector()/2 ), progConfig.COLOR_regStroke);
	}

	for (auto v: vertices){
		Vector normal (getNormalVector(*v));
		if (normal != Vector(0.0f, 0.0f, 0.0f))
			winMan->drawLine(*v, *v+normal / 2, progConfig.COLOR_regStroke);
	}
}



void Geometry::drawLines(float const* c)const{
//if there is only one vertex
	if (vertices.size() == 0)
		return;
	if (vertices.size() == 1)
	{
		winMan->setPix(static_cast<const Vector*>(vertices[0].get()), c);
		return;
	}

	for (auto edge: edges)
		winMan->drawLine(*edge->getHead(), *edge->getTail(), c);
	
}


void Geometry::transpose(){
	for (auto v: vertices){
		float temp = v->getX();
		v->setX(v->getY());
		v->setY(temp);
	}
}

// should be passing in pixel coordinate value
void Geometry::clip(const Vector& v){

	// convert unit;
	if (progConfig.clipMode == UP)
		clipUP(v.getY());
	else if (progConfig.clipMode == DOWN)
		clipDOWN(v.getY());	
	else if (progConfig.clipMode == LEFT)
		clipLEFT(v.getX());
	else if (progConfig.clipMode == RIGHT)
		clipRIGHT(v.getX());
}

void Geometry::clipUP(const float& y){
	// for each line 
	vertices.push_back(vertices[0]);

	std::vector<std::shared_ptr<Vector>>  newVs;
	bool hasKeptLast = false;
	// for every line
	for ( unsigned int i = 0; i < vertices.size()-1; i++){
		std::shared_ptr<Vector> v1 = vertices[i];
		std::shared_ptr<Vector>	v2 = vertices[i+1];
		std::shared_ptr<Vector>	intersect = getHorizontalIntersection(*v1, *v2, y);
		if (intersect == nullptr){
			if (v1->getY() < y ){
				if (!hasKeptLast)
					newVs.push_back(std::shared_ptr<Vector>( v1));
				newVs.push_back(std::shared_ptr<Vector>( v2));
				hasKeptLast = true;
				continue;
			}
			else{
				hasKeptLast = false;
				continue;
			} 
		}
		else{
			if (v1->getY() < y ){
				if (!hasKeptLast)
					newVs.push_back(std::shared_ptr<Vector>(v1));
				newVs.push_back(intersect);
				hasKeptLast = false;
				continue;
			}
			else{

				newVs.push_back(intersect);
				newVs.push_back(std::shared_ptr<Vector>(v2));
				hasKeptLast = true;
				continue;
			} 	
		}
	}

	
	if (newVs.size() == 0)
	{
		progConfig.curSelected=0;
		shader->deleteObj(dynamic_cast<Object*>(this) );
		return;
	}
	else{
		if(hasKeptLast)
			newVs.pop_back();
		vertices.clear();
		for (auto v: newVs){
			//v->print();
			vertices.push_back(v);
		}
	}
}

void Geometry::clipDOWN(const float&y){
	// for each line 
	vertices.push_back(vertices[0]);
//	std::cout << "Here" << std::endl;
	std::vector<std::shared_ptr<Vector>> newVs;
	bool hasKeptLast = false;
	// for every line
	for ( unsigned int i = 0; i < vertices.size()-1; i++){
		std::shared_ptr<Vector> v1 = vertices[i];
		std::shared_ptr<Vector>	v2 = vertices[i+1];
		std::shared_ptr<Vector>	intersect = getHorizontalIntersection(*v1, *v2, y);
		if (intersect == nullptr){
			if (v1->getY() > y ){
				if (!hasKeptLast)
					newVs.push_back(std::shared_ptr<Vector>( v1));
				newVs.push_back(std::shared_ptr<Vector>( v2));
				hasKeptLast = true;
				continue;
			}
			else{
				hasKeptLast = false;
				continue;
			} 
		}
		else{
			if (v1->getY() > y ){
				if (!hasKeptLast)
					newVs.push_back(std::shared_ptr<Vector>( v1 ));
				newVs.push_back(intersect);
				hasKeptLast = false;
				continue;
			}
			else{

				newVs.push_back(intersect);
				newVs.push_back(std::shared_ptr<Vector>(v2));
				hasKeptLast = true;
				continue;
			} 	
		}
	}

	if (newVs.size() == 0)
	{
		progConfig.curSelected = 0;
		shader->deleteObj(dynamic_cast<Object*>(this));
		return;
	}
	else{

		if(hasKeptLast)
			newVs.pop_back();
		vertices.clear();
		for (auto v: newVs){
			//v->print();
			vertices.push_back(v);
		}
	}
	
}

void Geometry::clipLEFT(const float& x){
	transpose();
	clipDOWN(x);
	transpose();

}

void Geometry::clipRIGHT(const float&x){
	transpose();
	clipUP(x);
	transpose();
}


std::shared_ptr<Vector> Geometry::getHorizontalIntersection(const Vector& v1, const Vector& v2, const float& y){
	float x1 = v1.getX(),
	 	  x2 = v2.getX(), 
	 	  y1 = v1.getY(), 
	 	  y2 = v2.getY();

	if ( (y1 < y && y2 < y) || (y1 > y && y2 > y) )
		return nullptr;

	float m = (x2 - x1) / (y2 - y1);

	float x = m*(y - y1) + x1;

	return std::shared_ptr<Vector>( new Vector(x, y, 0) );

}


std::shared_ptr<Vector> Geometry::getVerticalIntersection(const Vector& v1, const Vector& v2, const float& x){
	float x1 = v1.getX(),
	 	  x2 = v2.getX(), 
	 	  y1 = v1.getY(), 
	 	  y2 = v2.getY();

	if ( (x1 < x && x2 < x) || (x1 > x && x2 > x) )
		return nullptr;

	float m = (y2 - y1) / (x2 - x1);

	float y = m*(x - x1) + y1;

	return std::shared_ptr<Vector>( new Vector(x, y, 0) );
}

float Geometry::getMaxX()const{
	float ret = std::numeric_limits<float>::lowest();
	for (auto v: vertices)
		if (v->getX() > ret)
			ret = v->getX();

	return ret;
}

float Geometry::getMinX()const{
	float ret = std::numeric_limits<float>::max();
	for (auto v: vertices)
		if (v->getX() < ret)
			ret = v->getX();

	return ret;
}

float Geometry::getMaxY()const{
	float ret = std::numeric_limits<float>::lowest();
	for (auto v: vertices)
		if (v->getY() > ret)
			ret = v->getY();

	return ret;
}

float Geometry::getMinY()const{
	float ret = std::numeric_limits<float>::max();
	for (auto v: vertices)
		if (v->getY() < ret)
			ret = v->getY();

	return ret;
}

float Geometry::getMaxZ()const{
	float ret = std::numeric_limits<float>::lowest();
	for (auto v: vertices)
		if (v->getZ() > ret)
			ret =v->getZ();

	return ret;
}

float Geometry::getMinZ()const{
	float ret = std::numeric_limits<float>::max();
	for (auto v: vertices)
		if (v->getZ() < ret)
			ret = v->getZ();

	return ret;
}

Vector Geometry::getNormalVector(const Vector& v)const{
	if(vGetN(v) == -1)
		return Vector(0.0, 0.0, 0.0);
	float faceCnt = 0.0f;
	Vector normal;
	for (auto face:faces){
		if (face->hasVector(v)){
			faceCnt++;
			normal = normal + face->getNormalVector();
		}
	}
	return normal/faceCnt;
}




void Geometry::normalizeColors(const float &colorRate){
	// for (auto v:vertices)
	// 	v->setColor(v->getColor()[R]*colorRate, v->getColor()[G]*colorRate, v->getColor()[B]*colorRate);
}

std::ostream& operator << (std::ostream& stream, const Geometry& geo){
	//stream << "ID: " << shader->geoGetN(std::shared_ptr<Geometry>(&geo)) << std::endl;
	for( auto v: geo.vertices){
		stream << *v << std::endl;;
	
	} 
	return stream;
}

void Geometry::print(){ std::cout << *this << std::endl;}


std::shared_ptr<Vector> Geometry::getIntersection(const Line & line)const{
	
	std::vector<std::shared_ptr<Vector>> intersections;
	for (auto face: faces){
		std::shared_ptr<Vector> curIntersection = face->getIntersection(line);
		if ( curIntersection != nullptr)
			intersections.push_back(curIntersection);
	}

	if (intersections.size() <= 0 )
		return std::shared_ptr<Vector> (nullptr);

	if (intersections.size() > 1){
		sort(intersections.begin(), intersections.end(), 
			[ line](const std::shared_ptr<const Vector> & v1, const std::shared_ptr<const Vector> & v2) -> bool{
				return (*v1 - line.getOrigin()).length() < (*v2 - line.getOrigin()).length();
			});

		return intersections[0];
	}
	return intersections[0];
}

Vector Geometry::getNormal(const Vector & v)const{
	float minD = std::numeric_limits<float>::max();
	std::shared_ptr<Face> fSelect;
	for (auto face: faces){
		float curD = face->getDistance(v); 
		if ( curD < minD){
			fSelect = face;
			minD = curD;
		}
	}

	return fSelect->getNormalVector();
}