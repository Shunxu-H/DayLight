#include "Object.h"
#include "Face.h"
#include "Geometry.h"
#include "Edge.h"
#include "Curve.h"
#include "Vector.h"


Object::Object(const ObjType & oType):Matrix(4, 1){
	type = oType;
	data[0][3] = 1;
	reflectionCoefficient = 0.4;
	refractionCoefficient = 0.2;
}

// Object::Object(const Object & obj):Matrix(obj){
// 	type = obj.type;
// }


Object::Object(const Matrix & obj, const ObjType & oType):Matrix(obj){
	type = oType;
	reflectionCoefficient = 0.2;
	refractionCoefficient = 0.2;
}

void Object::transform(const Matrix & m){
	switch(type){

		case EDGE: 
			dynamic_cast<Edge*>(this)->transform(m);
			break;

		case CURVE: 
			dynamic_cast<Curve*>(this)->transform(m);
			break;
		case POLYHEDRON: 
			dynamic_cast<Geometry*>(this)->transform(m);
			break;
	}
}


void Object::deleteVertices(){
	switch(type){
		case EDGE: 
			dynamic_cast<Edge*>(this)->deleteVertices();
			break;
		case CURVE: 
			dynamic_cast<Curve*>(this)->deleteVertices();
			break;
		case POLYHEDRON: 
			dynamic_cast<Geometry*>(this)->deleteVertices();
			break;
	}
}


void Object::insert(std::shared_ptr<Vector> v){
	switch(type){
		case EDGE: 
			dynamic_cast<Edge*>(this)->insert(v);
			break;
		case CURVE: 
			dynamic_cast<Curve*>(this)->insert(v);
		case POLYHEDRON: 
			dynamic_cast<Geometry*>(this)->insert(v);
			break;
	}
}


void Object::push_front(std::shared_ptr<Vector> v){
	switch(type){
		case EDGE: 
			dynamic_cast<Edge*>(this)->push_front(v);
			break;
		case CURVE: 
			dynamic_cast<Curve*>(this)->push_front(v);
			break;
		case POLYGON: 
			dynamic_cast<Face*>(this)->push_front(v);
			break;
		case POLYHEDRON: 
			dynamic_cast<Geometry*>(this)->push_front(v);
			break;
	}
}
void Object::push_back(std::shared_ptr<Vector> v){
	switch(type){
		case EDGE: 
			dynamic_cast<Edge*>(this)->push_back(v);
			break;
		case CURVE: 
			dynamic_cast<Curve*>(this)->push_back(v);
			break;
		case POLYGON: 
			dynamic_cast<Face*>(this)->push_back(v);
			break;
		case POLYHEDRON: 
			dynamic_cast<Geometry*>(this)->push_back(v);
			break;
	}
}


void Object::selectVertices(const Vector & v1, const Vector & v2){
	switch(type){
		case EDGE: 
			dynamic_cast<Edge*>(this)->selectVertices(v1, v2);
			break;
		case CURVE: 
			dynamic_cast<Curve*>(this)->selectVertices(v1, v2);
			break;
		case POLYGON: 
			dynamic_cast<Face*>(this)->selectVertices(v1, v2);
			break;
		case POLYHEDRON: 
			dynamic_cast<Geometry*>(this)->selectVertices(v1, v2);
			break;
	}
}

char const *typeName[] =
{
	"VERTEX",
	"EDGE", 
	"CURVE",
	"POLYGON",
	"POLYHEDRON"
};

std::ostream& operator<< (std::ostream& stream, Object const *obj){
	switch(obj->type){
		case VERTEX: 
			stream << typeName[obj->type] << ": " << std::endl;
			stream << *dynamic_cast<Vector const*>(obj) << std::endl;

		case EDGE: 
			stream << typeName[obj->type] << ": " << std::endl;
			stream << *dynamic_cast<Edge const*>(obj) << std::endl;

		case CURVE: 
			stream << typeName[obj->type] << ": " << std::endl;
			stream << *dynamic_cast<Curve const*>(obj) << std::endl;

		case POLYGON: 
			stream << typeName[obj->type] << ": " << std::endl;
			stream << *dynamic_cast<Face const*>(obj) << std::endl;

		case POLYHEDRON: 
			stream << typeName[obj->type] << ": " << std::endl;
			stream << *dynamic_cast<Geometry const*>(obj) << std::endl;

	}
	return stream;
}

void Object::setColor(const float& r, const float& g, const float& b){
	color[R] = r;
	color[G] = g;
	color[B] = b;
}

Vector Object::getColor()const{
	return color;
}