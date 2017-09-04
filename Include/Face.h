#ifndef FACE_H
	#define FACE_H

#include <vector>
#include <memory>
#include "Index.h"
#include "Line.h"
class Edge;
class AEL;

class Face
{
public:
    Face();
    ~Face();

    void addV(std::shared_ptr<Vector> v);
    void setVertexIndeces(const int & n1, const int & n2, const int & n3);
    void setUvIndeces(const int & n1, const int & n2, const int & n3);
    void setNormalIndeces(const int & n1, const int & n2, const int & n3);

    inline const std::vector<unsigned int> &
        verticesInds() const { return _verticesIndeces; }
    inline const std::vector<unsigned int> &
        uvInds() const { return _uvIndeces; }
    inline const std::vector<unsigned int> &
        normalInds() const { return _normalIndeces; }

	std::shared_ptr<Vector> getV(const unsigned int & index)const;

	bool hasVector(const Vector&)const;
	int getVerticesCnt()const{return vertices.size();}

	std::vector<AEL*> getAELs(const float& pixelUnit, const float& w_x, const float& w_y, const float& w_z, const INDEX &, const INDEX &)const;

	Face inPXLCOORD(const float& pixelUnit, const float& w_x, const float& w_y, const float& w_z)const;
	void print();
	Vector getNormalVector()const;
	Vector getCentroid();
    const std::vector<std::shared_ptr<Vector>>& getVertices()const{ return vertices;}

	
	std::shared_ptr<Vector> getIntersection(const Line & line)const;


	std::string save()const;
	void clear();
	void transform(const Matrix & m);
	void draw(float const*)const;
    void insert(std::shared_ptr<Vector> v){}
    void deleteVertices(){}

    friend std::ostream& operator<< (std::ostream& stream, const Face & f);
	
    void push_front(std::shared_ptr<Vector> v){}
    void push_back(std::shared_ptr<Vector> v){}

    void selectVertices(const Vector & v1, const Vector & v2){}

	bool contain(const Vector & point)const;
	float getDistance(const Vector & point)const;

protected:

private:
    std::vector<unsigned int> _verticesIndeces;
    std::vector<unsigned int> _uvIndeces;
    std::vector<unsigned int> _normalIndeces;

	void toPXLPOS(const float& pixelUnit, const float& w_x, const float& w_y, const float& w_z);
	std::vector<std::shared_ptr<Vector>> vertices;

};



	#endif
