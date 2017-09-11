#ifndef FACE_H
	#define FACE_H

#include <vector>
#include <memory>
#include "Index.h"
class Edge;
class AEL;

class Face
{
public:
    Face();
    ~Face();

    void setVertexIndeces(const int & n1, const int & n2, const int & n3);
    void setUvIndeces(const int & n1, const int & n2, const int & n3);
    void setNormalIndeces(const int & n1, const int & n2, const int & n3);

    inline void
        addVertexIndex( const int & indx ) { _verticesIndeces.push_back(indx); }
    inline void
        addUvIndex( const int & indx ) { _uvIndeces.push_back(indx); }
    inline void
        addNormalIndex( const int & indx ) { _normalIndeces.push_back(indx); }

    inline const std::vector< int > &
        getVerticesInds() const { return _verticesIndeces; }
    inline const std::vector< int > &
        getUvInds() const { return _uvIndeces; }
    inline const std::vector< int > &
        getNormalInds() const { return _normalIndeces; }



protected:

private:
    std::vector< int > _verticesIndeces;
    std::vector< int > _uvIndeces;
    std::vector< int > _normalIndeces;


};



	#endif
