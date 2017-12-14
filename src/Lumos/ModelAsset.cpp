/*
The MIT License (MIT)

Copyright (c) 2016-2017 Shunxu Huang

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
#include "ModelAsset.h"

#include "Extern.h"


using namespace Lumos;



void Material::loadUniforms() const{

    if (gProgram->hasUniform("tex")){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, glTexId);
        gProgram->setUniform("tex", 0);
        //set to 0 because the texture is bound to GL_TEXTURE0
    }
    if (gProgram->hasUniform("transmittance")){
        gProgram->setUniform("transmittance", transmittance);
    }
    if (gProgram->hasUniform("hasTexture")){
        gProgram->setUniform("hasTexture", !texture.empty());
    }
    if (gProgram->hasUniform("diffuseColor"))
        gProgram->setUniform("diffuseColor", diffuseColor );

    if (gProgram->hasUniform("ambient"))
        gProgram->setUniform("ambient", color3(0.05f, 0.05f, 0.05f) );

    if (gProgram->hasUniform("materialShininess"))
        gProgram->setUniform("materialShininess", reflexitivity );

    if (gProgram->hasUniform("materialSpecularColor"))
        gProgram->setUniform("materialSpecularColor", specular);

}
