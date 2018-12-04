/*
The MIT License (MIT)

Copyright (c) 2016-2018, Shunxu Huang, shunxuhuang@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#ifndef FACE_H
	#define FACE_H

#include <vector>
#include <memory>
#include <Patronus/Instance.h>

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


    inline void
        setMaterial( Lumos::Material * m_ptr ) { _material = m_ptr; }
    inline Lumos::Material *
        getMaterial( ) const { return _material; }



protected:

private:
    std::vector< int > _verticesIndeces;
    std::vector< int > _uvIndeces;
    std::vector< int > _normalIndeces;

    Lumos::Material *  _material;



};



	#endif
