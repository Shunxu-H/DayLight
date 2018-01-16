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
#include "GL_include.h"
#include "Transformable.h"


using namespace Patronus;


void Transformable::translate ( const float & x, const float & y, const float & z ){
    _translate += point3( x, y, z );
}

void Transformable::scale ( const float & x, const float & y, const float & z ){
    _scale *= point3( x, y, z );
}

void Transformable::rotate ( const float & x, const float & y, const float & z ){
    _orientation += point3( x, y, z );
}


glm::mat4 Transformable::getModelMatrix() const{
    glm::mat4 ret = glm::mat4(1);
    ret = glm::rotate(ret, _orientation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    ret = glm::rotate(ret, _orientation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    ret = glm::rotate(ret, _orientation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    ret = glm::translate(ret, _translate );
    return ret;
}

glm::mat4 Transformable::getInverseModelMatrix() const{
    return glm::inverse(getModelMatrix());
}
