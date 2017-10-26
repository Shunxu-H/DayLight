#include "Face.h"

Face::Face(){

}



void Face::setVertexIndeces(const int & n1, const int & n2, const int & n3){
    _verticesIndeces = std::vector< int >({n1, n2, n3});
}

void Face::setUvIndeces(const int & n1, const int & n2, const int & n3){
    _uvIndeces = std::vector< int >({n1, n2, n3});

}

void Face::setNormalIndeces(const int & n1, const int & n2, const int & n3){
    _normalIndeces = std::vector< int >({n1, n2, n3});

}


Face::~Face(){
	
}

