#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cstring>
#include <queue>
#include <limits>
#include <cmath>
#include <climits>
#include <algorithm>
#include <memory>
#include "Shader.h"
#include "Config.h"
#include "OrthoView.h"
#include "Edge.h"
#include "Geometry.h"
#include "WindowManager.h"
#include "Utility.h"
#include "Face.h"
#include "Ellipsoid.h"
#include "Vector.h"
#include "Curve.h"
#include "CVM.h"

extern Config progConfig;
extern std::vector<std::shared_ptr<Vector>> vertexBuffer;
extern WindowManager* winMan;


Shader::Shader(const std::string& file){
	lightSource = Vector(0.0f, 20.0f, 0.0f);
	viewPtr = Vector(0.0f, 0.0f, 2.0f); 
	//coordinate = new Coordinate();
	fileName = file;
	rotationVector = Edge( std::shared_ptr<Vector>(new Vector(0.0f, 0.0f, 0.0f)) , std::shared_ptr<Vector>(new Vector(1.0f, 1.0f, 1.0f)));
}

Shader::~Shader(){
}



void Shader::addObj( std::shared_ptr<Object> newObj ){
	if (!newObj.get())
	 	return;
	// if (newObj->isType(PXLPOS)){
	// 	std::cout << "ERROR: unconverted objects being pushed.Ignore." << std::endl;
	// 	return;
	// }

	objects.push_back(newObj); 
	if (objects.size() == 1)
		curSelection = objects[0];
}

void Shader::loadFile (const std::string& _fileName){
	std::fstream f;
	if (_fileName.size() > 0)
		f.open(_fileName.c_str());
	else 
		f.open(fileName.c_str());

	if (!f.is_open())
	{
		std::cerr << "ERROR: Can't open file " << fileName << std::endl;
		return;
	}

	std::stringstream fss;
	fss << f.rdbuf();

	f.close();
	
	std::deque<std::string> tokens = mystrtok( fss.str(), " \n");

	int vCnt = 0, eCnt = 0, fCnt = 0;

	while (!tokens.empty()){
		ObjType type = static_cast<ObjType>(stoi(tokens[0]));
		tokens.pop_front(); 
		Object *newObj; 
		
		if (type == POLYHEDRON){
			Geometry *newG = new Geometry();

			// load color
			newG->setColor(stof(tokens[R]), stof(tokens[G]), stof(tokens[B]));
			tokens.pop_front();
			tokens.pop_front();
			tokens.pop_front();
			
			// load vertexes
			vCnt = atoi( tokens.front().c_str());
			tokens.pop_front();
			for ( int i = 0; i < vCnt; i++){
				float x = stof(tokens.front());
				tokens.pop_front();
				float y = stof(tokens.front());
				tokens.pop_front();
				float z = stof(tokens.front());
				tokens.pop_front();

				*newG += std::shared_ptr<Vector>( new Vector(x, y, z) );
			}

			// load edges
			eCnt = atoi( tokens.front().c_str());
			tokens.pop_front();
			
			for ( int i = 0; i < eCnt; i++){
				
				int headItr = stoi(tokens.front());
				tokens.pop_front();
				int tailItr = stoi(tokens.front());
				tokens.pop_front();

				*newG += std::shared_ptr<Edge>( new Edge(newG->nGetV(headItr), newG->nGetV(tailItr)));
			}

			// load faces
			fCnt = atoi( tokens.front().c_str());
			tokens.pop_front();
			
			// assuming each face has exactly 3 vertices
			for ( int i = 0; i < fCnt; i++){
				std::shared_ptr<Face> newFace(new Face());
				
					newFace->addV(newG->nGetV(stoi(tokens.front())));
				tokens.pop_front();
				
				newFace->addV(newG->nGetV(stoi(tokens.front())));
				tokens.pop_front();
				
				newFace->addV(newG->nGetV(stoi(tokens.front())));
				tokens.pop_front();

				*newG += newFace;
			}

			
			newG->updateCentroid();
			addObj(std::shared_ptr<Geometry>(newG));
		}
		else if (type == ELLIPSOID){
			Ellipsoid *newE = new Ellipsoid();

			// load color
			newE->setColor(stof(tokens[R]), stof(tokens[G]), stof(tokens[B]));
			tokens.pop_front();
			tokens.pop_front();
			tokens.pop_front();


			newE->setCenter(Vector(stof(tokens[X]), stof(tokens[Y]), stof(tokens[Z] )));
			tokens.pop_front();
			tokens.pop_front();
			tokens.pop_front();


			newE->setOffset(Vector(stof(tokens[X]), stof(tokens[Y]), stof(tokens[Z])));
			tokens.pop_front();
			tokens.pop_front();
			tokens.pop_front();

			addObj(std::shared_ptr<Ellipsoid>(newE));
		}
		else if (type == CURVE){
			Curve *newC = new Curve();


	// // dump k
	// str.append(std::to_string(k) + "\n");
	// // dump resolution 
	// str.append(std::to_string(resolution) + "\n");
	// // dump u vector
	// str.append(std::to_string(u.size()) + "\n");
	// for(const float & num: u)
	// 	str.append(std::to_string(num) + " ");
	// str.append("\n");
			newC->setK(std::atoi(tokens.front().c_str()));
			tokens.pop_front();
			newC->setResolution(std::atoi(tokens.front().c_str()));
			tokens.pop_front();

			int uCnt = std::atoi(tokens.front().c_str());
			tokens.pop_front();
			std::vector<float> uVector;
			for ( int i = 0; i < uCnt; i++){
				uVector.push_back(std::stof(tokens.front().c_str()));
				tokens.pop_front();
			}

			
			// load vertexes
			vCnt = atoi( tokens.front().c_str());
			tokens.pop_front();
			for ( int i = 0; i < vCnt; i++){
				float x = stof(tokens.front());
				tokens.pop_front();
				float y = stof(tokens.front());
				tokens.pop_front();
				float z = stof(tokens.front());
				tokens.pop_front();
				std::cout << Vector(x, y, z) << std::endl;
				*newC += std::shared_ptr<Vector>( new Vector(x, y, z) );
			}
			setUVector(uVector);
			addObj(std::shared_ptr<Curve>(newC));

		}

	}
	//std::cout << size() << std::endl;

	// // if( size() > 0)
	// 	winMan->reshapeWindows();
	drawAll();

}


std::shared_ptr<Object> Shader::getCurSelection()const{
	return curSelection;
}


void Shader::clear(){
	for (auto geo: objects){
		geo->clear();
	}
//std::cout << "clear" << std::endl;
	objects.clear();
}


void Shader::deleteObj(Object const* g){
	std::vector<std::shared_ptr<Object>>::iterator itr = objects.begin();


	for( ; itr != objects.end(); itr++){
		if (itr->get() == g)
		{
			objects.erase(itr);
			break;
		}
	}


	if(isSelected(g)){
		if(objects.size() > 0)
			curSelection = objects[0];
		else
			curSelection = std::shared_ptr<Object>(nullptr);
	}
}

void Shader::deleteVertices(){
	if(curSelection != nullptr){
		curSelection->deleteVertices();
	}
}


void Shader::save(const std::string& fileName){
	std::string str="";

	for ( auto object : objects)	
		str.append(object->save());

	//std::cout <<  str << std::endl;
	std::ofstream ofs (fileName.c_str(), std::ofstream::out);

	if(!ofs.is_open())
		std::cerr << "Invalid fileName in Coordinate::save(const std::string& fileName)" << std::endl;

	ofs << str; 

	ofs.close();
}

/*
float Shader::getColorNormalizeRate()const{
	float max = std::numeric_limits<float>::min();

	for (auto geo:objects){
		float curMax = geo->getHighestColor();
		if(curMax > max)
			max = curMax;
	}

	return 1.0f/max;
}

void Shader::normalizeColors(const float& colorRate )const{

	for (auto geo:objects){
		geo->normalizeColors(colorRate);
	}

}
*/

void Shader::drawAll(){
	// compute all the colors

	for (auto obj: objects){
		obj->draw(progConfig.COLOR_regStroke);	
	}


	/*
	for( auto geo: objects)
		geo->computeColors(lightSource, viewPtr);
	normalizeColors(getColorNormalizeRate());

	if(progConfig.fillMode == FILL && progConfig.opMode != TRANSFORM ) {
		winMan->fillPolygons(objects);
	}
	else if (progConfig.fillMode == HALFTONE){
		for (auto geo:objects){
			winMan->halfToning(*geo);
		}
	}
	else {
		for (unsigned int i = 0; i < size(); i++){
			//objects[i]->print();
			curRendering = objects[i];
			objects[i]->draw();
		}
	}


	// draw normals 
	if(progConfig.showNormal == true){	
		for (auto geo:objects){
			geo->drawNormal();
		}
	
	}


	drawLight();
	*/
}


std::shared_ptr<Object> Shader::nGetGeo(const unsigned int &index )const {
	if (index >= size())
		return nullptr;
	else 
		return objects[index];
}

int Shader::geoGetN(const Object* obj)const {
	for ( unsigned int i = 0; i < objects.size(); i++)
		if (objects[i].get() == obj )
			return i;
	return -1;
}
/*

float Shader::getMaxX()const{
	float ret = std::numeric_limits<float>::lowest();
	for (auto geo: objects)
		if (geo->getMaxX() > ret)
			ret = geo->getMaxX();

	return ret;
}

float Shader::getMinX()const{
	float ret = std::numeric_limits<float>::max();
	for (auto geo: objects)
		if (geo->getMinX() < ret)
			ret = geo->getMinX();

	return ret;
}

float Shader::getMaxY()const{
	float ret = std::numeric_limits<float>::lowest();
	for (auto geo: objects)
		if (geo->getMaxY() > ret)
			ret = geo->getMaxY();

	return ret;
}

float Shader::getMinY()const{
	float ret = std::numeric_limits<float>::max();
	for (auto geo: objects)
		if (geo->getMinY() < ret)
			ret = geo->getMinY();

	return ret;
}

float Shader::getMaxZ()const{
	float ret = std::numeric_limits<float>::lowest();
	for (auto geo: objects)
		if (geo->getMaxZ() > ret)
			ret = geo->getMaxZ();

	return ret;
}

float Shader::getMinZ()const{
	float ret = std::numeric_limits<float>::max();
	for (auto geo: objects)
		if (geo->getMinZ() < ret)
			ret = geo->getMinZ();

	return ret;
}

*/
void Shader::print()const{
	for (auto geo: objects)
		std::cout << geo.get() << std::endl;
}



void Shader::drawLight()const{
	Vector dir[27];

	for (int i = -1; i <= 1; i++){
		for (int j = -1; j <= 1; j++){
			for (int k = -1; k <= 1; k++){
				winMan->drawLine(lightSource, lightSource + Vector(i, j, k).makeUnitVector() / 2, Color().WHITE);
			}
		}
	}
}

void Shader::moveLight(const Vector& newPos){
	lightSource = newPos;
	std::cout << lightSource << std::endl;
}


void Shader::moveView(const Vector& newPos){
	lightSource = newPos;
	std::cout << lightSource << std::endl;
}

void Shader::shiftSelectionUp(){
	if (objects.size() <= 1)
		return;
	int index = geoGetN(curSelection.get());
	int newIndex;
	if (index == 0)
		newIndex = objects.size() - 1;
	else
		newIndex = index - 1;
	curSelection = objects[newIndex];
}

void Shader::shiftSelectionDown(){
	if (objects.size() <= 1)
		return;

	int newIndex = (geoGetN(curSelection.get())+1) % objects.size();
	curSelection = objects[newIndex];
}


void Shader::selectVertices(const Vector & v1, const Vector & v2){
	if( curSelection == nullptr)
		return;
	else
		curSelection->selectVertices(v1, v2);
	//curSelection->selectVertices(v1, v2);


}

void Shader::insert(std::shared_ptr<Vector> v){
	if( curSelection == nullptr)
		return;
	else
		curSelection->insert(v);
}


void Shader::push_front(std::shared_ptr<Vector> v){
	if( curSelection == nullptr)
		return;
	else
		curSelection->push_front(v);
}

void Shader::push_back(std::shared_ptr<Vector> v){
	if( curSelection == nullptr)
		return;
	else
		curSelection->push_back(v);
}


void Shader::setK(const int & k){
	if(curSelection == nullptr){
		std::cerr << "No object seleted" << std::endl;
		return;
	}
	else if(curSelection->getType() != CURVE){
		std::cerr << "Seleted Object is not a curve" << std::endl;
		return;
	}

	dynamic_cast<Curve*>(curSelection.get())->setK(k);


}

void Shader::setUVector(const std::vector<float> & us){
	if(curSelection == nullptr){
		std::cerr << "No object seleted" << std::endl;
		return;
	}
	else if(curSelection->getType() != CURVE){
		std::cerr << "Seleted Object is not a curve" << std::endl;
		return;
	}

	dynamic_cast<Curve*>(curSelection.get())->setUVector(us);
}

void Shader::setOneU(const int & index, const float & value){

	if(curSelection == nullptr){
		std::cerr << "No object seleted" << std::endl;
		return;
	}
	else if(curSelection->getType() != CURVE){
		std::cerr << "Seleted Object is not a curve" << std::endl;
		return;
	}

	dynamic_cast<Curve*>(curSelection.get())->setOneU(index, value);
}

void Shader::toggleCurveType(){
	if(curSelection == nullptr){
		std::cerr << "No object seleted" << std::endl;
		return;
	}
	else if(curSelection->getType() != CURVE){
		std::cerr << "Seleted Object is not a curve" << std::endl;
		return;
	}
	dynamic_cast<Curve*>(curSelection.get())->toggleType();

}

void Shader::setResolution(const int & res){
	if(curSelection == nullptr){
		std::cerr << "No object seleted" << std::endl;
		return;
	}
	else if(curSelection->getType() != CURVE){
		std::cerr << "Seleted Object is not a curve" << std::endl;
		return;
	}
	dynamic_cast<Curve*>(curSelection.get())->setResolution(res);

}


Vector Shader::rayTrace(const Line & view)const{

	std::pair<Vector, std::shared_ptr<const Object>> found = getIntersection(view);
	if(found.second != nullptr){
		return phong(found.first, view.getOrigin(), found.second, 3);
		//returnn Vector(1, 1, 1);
	}

	return Vector(-1, -1, -1);
}


Vector Shader::phong(const Vector& p, const Vector &viewPtr, const std::shared_ptr<const Object> & obj, const unsigned int & levelLeft)const{	
	Vector Ia = obj->getColor(); // color of the object
	double ka = 0.6, kd=0.8, ks=0.5, phoneCoefficient = 3.0;
	double c = (lightSource - p).length();
	Vector n = obj->getNormal(p).makeUnitVector();
	Vector l = (lightSource - p).makeUnitVector();
	Vector v = (viewPtr - p).makeUnitVector();
	Vector r = l.getReflectionVector(n).makeUnitVector();
	double cosalpha = n.dot(lightSource);
	double cosbeta = v.dot(r);

	if (cosalpha < 0)
		cosalpha = 0;
	if (cosbeta < 0)
		cosbeta = 0;

	Vector Il (1.0f, 1.0f, 1.0f);
	Vector I_local;
	if (!isCasted(lightSource, p))
		I_local = Ia*ka + ( Il.times(Ia)/((viewPtr - v).length() + c ) )*(kd*cosalpha + ks*pow(cosbeta, phoneCoefficient));
 	else 
 		I_local = Ia*ka;

 	if (levelLeft <= 0)
 		return I_local;

 	// std::shared_ptr<Vector> intersection = getIntersection();
 	Vector I_reflection;
 	Vector I_refraction; 

	std::pair<Vector, std::shared_ptr<const Object>> found = getIntersection(Line(p, v.getReflectionVector(n)));
	if(found.second != nullptr){
		I_reflection = phong(found.first, p, found.second, levelLeft-1);
	}
	else 
		I_reflection = Vector();

 	// Vector I_global;

	return I_local + ( I_reflection * obj->getReflectionCoefficient());
}

bool Shader::isCasted(const Vector & light, const Vector & p)const{
	Vector l2p = light - p;
	std::pair<Vector, std::shared_ptr<const Object>> found = getIntersection(Line(p, l2p));
	if(found.second != nullptr && l2p.length() > (found.first - p).length()){
		return true;
	}
	else 
		return false;

}

/**
This function will return 
if no intersection found => a pair of (Vector(0, 0, 0) and nullptr) 
Otherwise => std::pair(intersected point, intersected object)
**/
std::pair<Vector, std::shared_ptr<const Object>> Shader::getIntersection(const Line & view)const{
	std::vector<std::pair<Vector, std::shared_ptr<const Object>>> found;
	for (const std::shared_ptr<const Object> object: objects){
		std::shared_ptr<Vector> curIntersection = object->getIntersection(view);
		if(curIntersection != nullptr){
			found.push_back(std::pair<Vector, std::shared_ptr<const Object>>(*curIntersection, object));
		}
	}
	if ( found.size() == 0)
		return std::pair<Vector, std::shared_ptr<const Object>>(Vector(),std::shared_ptr<Object>( nullptr ));

	sort(found.begin(), found.end(), 
		[ &, view](const std::pair<Vector, std::shared_ptr<const Object>>  & p1, const std::pair<Vector, std::shared_ptr<const Object>> & p2) -> bool{
			return (p1.first - view.getOrigin()).length() > (p2.first - view.getOrigin()).length();
		});

	return found[0];
}