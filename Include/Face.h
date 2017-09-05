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

    inline const std::vector<unsigned int> &
        verticesInds() const { return _verticesIndeces; }
    inline const std::vector<unsigned int> &
        uvInds() const { return _uvIndeces; }
    inline const std::vector<unsigned int> &
        normalInds() const { return _normalIndeces; }



protected:

private:
    std::vector<unsigned int> _verticesIndeces;
    std::vector<unsigned int> _uvIndeces;
    std::vector<unsigned int> _normalIndeces;


};



	#endif
