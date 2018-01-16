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
#include "Light.h"

using namespace Patronus;


Light Light::makeDirectionalLight(const point3 & position, const point3 & intensity, const float & ambientCoefficient){
    Light directionalLight(position);
    directionalLight._type = LightType::DIRECTIONAL;
    directionalLight._intensity = intensity; //weak yellowish light
    directionalLight._ambientCoefficient = ambientCoefficient;
    return directionalLight;
}

Light Light::makePointLight( const point3 & position,
                      const color3 & intensity,
                      const float & attenuation,
                      const float & ambientCoeffient,
                      const float & coneAngle,
                      const glm::vec3 & coneDirection){
    Light spotlight(position);
    spotlight._type = LightType::SPOT;
    spotlight._intensity = intensity; //strong white light
    spotlight._attenuation = attenuation;
    spotlight._ambientCoefficient = ambientCoeffient; //no ambient light
    spotlight._coneAngle = coneAngle;
    spotlight._coneDirection = coneDirection;
    return spotlight;
}
