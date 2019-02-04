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
#include <stdexcept>
#include <vector>
#include <experimental/filesystem>
#include "Common/GL_include.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Lumos/Program.h>
#include <IO/WindowManager.h>

#include <Patronus/Shaper.h>
#include <Patronus/PhysicalWorld.h>

#include <ArrayBuffer.h>
#include <Common/Utility.h>
#include <Common/Extern.h>

using namespace Daylight::Lumos; 

std::unordered_map<std::string, ShadingPipe> Program::_shading_pipes{}; 

Program::Program()
    : GLObject(glCreateProgram(), [](GLuint* o) {glDeleteProgram(*o);}
    )
{
    if( getObjId() == 0 )
        throw std::runtime_error( "glCreateProgram Failed" );
}


std::vector<std::string> Program::getAllShadingPipeNames() const{
    std::vector<std::string> ret{}; 
    for(auto it = _shading_pipes.begin(); it != _shading_pipes.end(); ++it) {
        ret.push_back(it->first);
    }
    return ret; 
}

void Program::enableShadingPipe( const std::string & pipe_name ){
    assert( _shading_pipes.find( pipe_name ) != _shading_pipes.end() );
    GLint progId = getObjId(); 

    Utils::logOpenGLError( std::string(__FUNCTION__) + ":" + std::to_string(__LINE__) );
    _shading_pipes[pipe_name].use(&progId);

    Utils::logOpenGLError( std::string(__FUNCTION__) + ":" + std::to_string(__LINE__) );
    glLinkProgram(_glObjId);
}

void Program::disableShadingPipe( const std::string & pipe_name ){
    assert( _shading_pipes.find( pipe_name ) != _shading_pipes.end() ); 
    GLint progId = _glObjId; 
    _shading_pipes[pipe_name].stopUsing(&progId);
}

void Program::loadShaders( const std::string & GLSL_path ){

    {
        namespace fs = std::experimental::filesystem;
        std::cout << fs::current_path() << std::endl;
        for (const auto & p : fs::directory_iterator(GLSL_path))
        {
            std::string curExtension = fs::path(p).extension();
            std::string curFileName = fs::path(p).filename();
            curFileName = curFileName.substr(0, curFileName.size() - curExtension.size());

            if ( _shading_pipes.find(curFileName) == _shading_pipes.end() ) // not found 
                Program::_shading_pipes[curFileName] = ShadingPipe();

            if ( std::string( fs::path(p).extension() ).compare(".vert") == 0 )
                Program::_shading_pipes[curFileName].addShader( Shader::readFromFile( fs::path( p ), GL_VERTEX_SHADER )) ;
            else if ( std::string( fs::path(p).extension() ).compare(".frag") == 0 )
                Program::_shading_pipes[curFileName].addShader( Shader::readFromFile( fs::path( p ), GL_FRAGMENT_SHADER ));
        }

    }

    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    for (auto it:_shading_pipes)
        it.second.verify(); 

}


void Program::preDrawSetUp() {
    //use();
    GLError( __PRETTY_FUNCTION__ , __LINE__ );

    for ( auto & m : shaper->getMeshes())
        world->loadInstance(m);

    // compute bounding box
    if (world->getInstances().size() > 0)
        winMan->positionAllViewsToFitAllInstances();

    GLError( __PRETTY_FUNCTION__ , __LINE__ );
}

void Program::use(void * data) const {
    glUseProgram( getObjId() );
}

bool Program::isInUse() const {
    GLint currentProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    return (currentProgram == static_cast<GLint>( getObjId() ));
}

void Program::stopUsing(void * data) const {
    glUseProgram(0);
}

void Program::bind() const{
    glLinkProgram( getObjId() );
}

std::vector<std::string> Program::getCurrentActiveAttributes(const size_t & maxLengthForName){
    // load attributes
    GLint count;

    GLint size; // size of the variable
    GLenum type; // type of the variable (float, vec3 or mat4, etc)

    GLchar name[maxLengthForName]; // variable name in GLSL
    GLsizei length; // name length

    // load attributes
    glGetProgramiv(getObjId(), GL_ACTIVE_ATTRIBUTES, &count);
    //printf("Active Attributes: %d\n", count);
    std::vector<std::string> attributes(count); 
    for (int i = 0; i < count; i++)
    {
        glGetActiveAttrib(getObjId(), i, maxLengthForName, &length, &size, &type, name);

        //qDebug() << "Attribute " << i << "Type:" << type << " Name: " << name;
        attributes.push_back( name );
    }
    return attributes; 

}

std::vector<std::string> Program::getCurrentActiveUniforms(const size_t & maxLengthForName){
    // load attributes
    GLint count;

    GLint size; // size of the variable
    GLenum type; // type of the variable (float, vec3 or mat4, etc)

    GLchar name[maxLengthForName]; // variable name in GLSL
    GLsizei length; // name length
    // load uniform
    glGetProgramiv(getObjId(), GL_ACTIVE_UNIFORMS, &count);
    //printf("Active Uniforms: %d\n", count);
    std::vector<std::string> uniforms(count); 
    for (int i = 0; i < count; i++)
    {
        glGetActiveUniform(getObjId(), (GLuint)i, maxLengthForName, &length, &size, &type, name);

        uniforms.push_back( name );
    }
    return uniforms; 
} 


GLint Program::getAttrib(const GLchar* attribName) const {
    if(!attribName)
        throw std::runtime_error("attribName was NULL");

    GLint attrib = glGetAttribLocation( getObjId(), attribName );
    if(attrib == -1)
        throw std::runtime_error(std::string("Program attribute not found: ") + attribName);

    return attrib;
}


bool Program::hasAttribute( const GLchar * attribName ) const {
    if(!attribName)
        return false;
    GLint uniform = glGetAttribLocation( getObjId(), attribName );
    if(uniform == -1)
        return false;

    return true;
}

GLint Program::getUniform(const GLchar* uniformName) const {
    if(!uniformName)
        throw std::runtime_error("uniformName was NULL");

    GLint uniform = glGetUniformLocation( getObjId(), uniformName );
    if(uniform == -1)
        throw std::runtime_error(std::string("Program uniform not found: ") + uniformName);

    return uniform;
}

bool Program::hasUniform( const GLchar * uniformName ) const {
    if(!uniformName)
        return false;
    GLint uniform = glGetUniformLocation( getObjId(), uniformName );
    if(uniform == -1)
        return false;

    return true;
}

#define ATTRIB_N_UNIFORM_SETTERS(OGL_TYPE, TYPE_PREFIX, TYPE_SUFFIX) \
\
    void Program::setAttrib(const GLchar* name, OGL_TYPE v0) \
        { /* assert(isInUse());  */if (hasAttribute(name)) glVertexAttrib ## TYPE_PREFIX ## 1 ## TYPE_SUFFIX (getAttrib(name), v0); } \
    void Program::setAttrib(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1) \
        { /* assert(isInUse());  */if (hasAttribute(name))glVertexAttrib ## TYPE_PREFIX ## 2 ## TYPE_SUFFIX (getAttrib(name), v0, v1); } \
    void Program::setAttrib(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2) \
        { /* assert(isInUse());  */if (hasAttribute(name))glVertexAttrib ## TYPE_PREFIX ## 3 ## TYPE_SUFFIX (getAttrib(name), v0, v1, v2); } \
    void Program::setAttrib(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3) \
        { /* assert(isInUse());  */if (hasAttribute(name))glVertexAttrib ## TYPE_PREFIX ## 4 ## TYPE_SUFFIX (getAttrib(name), v0, v1, v2, v3); } \
\
    void Program::setAttrib1v(const GLchar* name, const OGL_TYPE* v) \
        { /* assert(isInUse());  */if (hasAttribute(name))glVertexAttrib ## TYPE_PREFIX ## 1 ## TYPE_SUFFIX ## v (getAttrib(name), v); } \
    void Program::setAttrib2v(const GLchar* name, const OGL_TYPE* v) \
        { /* assert(isInUse());  */if (hasAttribute(name))glVertexAttrib ## TYPE_PREFIX ## 2 ## TYPE_SUFFIX ## v (getAttrib(name), v); } \
    void Program::setAttrib3v(const GLchar* name, const OGL_TYPE* v) \
        { /* assert(isInUse());  */if (hasAttribute(name))glVertexAttrib ## TYPE_PREFIX ## 3 ## TYPE_SUFFIX ## v (getAttrib(name), v); } \
    void Program::setAttrib4v(const GLchar* name, const OGL_TYPE* v) \
        { /* assert(isInUse());  */if (hasAttribute(name))glVertexAttrib ## TYPE_PREFIX ## 4 ## TYPE_SUFFIX ## v (getAttrib(name), v); } \
\
    void Program::setUniform(const GLchar* name, OGL_TYPE v0) \
        { /* assert(isInUse());  */if (hasUniform(name))glUniform1 ## TYPE_SUFFIX (getUniform(name), v0); } \
    void Program::setUniform(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1) \
        { /* assert(isInUse());  */if (hasUniform(name))glUniform2 ## TYPE_SUFFIX (getUniform(name), v0, v1); } \
    void Program::setUniform(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2) \
        { /* assert(isInUse());  */if (hasUniform(name))glUniform3 ## TYPE_SUFFIX (getUniform(name), v0, v1, v2); } \
    void Program::setUniform(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3) \
        { /* assert(isInUse());  */if (hasUniform(name))glUniform4 ## TYPE_SUFFIX (getUniform(name), v0, v1, v2, v3); } \
\
    void Program::setUniform1v(const GLchar* name, const OGL_TYPE* v, GLsizei count) \
        { /* assert(isInUse());  */if (hasUniform(name)) glUniform1 ## TYPE_SUFFIX ## v (getUniform(name), count, v); } \
    void Program::setUniform2v(const GLchar* name, const OGL_TYPE* v, GLsizei count) \
        { /* assert(isInUse());  */if (hasUniform(name)) glUniform2 ## TYPE_SUFFIX ## v (getUniform(name), count, v); } \
    void Program::setUniform3v(const GLchar* name, const OGL_TYPE* v, GLsizei count) \
        { /* assert(isInUse());  */if (hasUniform(name)) glUniform3 ## TYPE_SUFFIX ## v (getUniform(name), count, v); } \
    void Program::setUniform4v(const GLchar* name, const OGL_TYPE* v, GLsizei count) \
        { /* assert(isInUse());  */if (hasUniform(name)) glUniform4 ## TYPE_SUFFIX ## v (getUniform(name), count, v); }


ATTRIB_N_UNIFORM_SETTERS(GLfloat, , f);
ATTRIB_N_UNIFORM_SETTERS(GLint, I, i);
ATTRIB_N_UNIFORM_SETTERS(GLuint, I, ui);

void Program::setUniformMatrix2(const GLchar* name, const GLfloat* v, GLsizei count, GLboolean transpose) {
    // assert(isInUse());
    if (hasUniform(name))
        glUniformMatrix2fv(getUniform(name), count, transpose, v);
}

void Program::setUniformMatrix3(const GLchar* name, const GLfloat* v, GLsizei count, GLboolean transpose) {
    // assert(isInUse());
    if (hasUniform(name))
        glUniformMatrix3fv(getUniform(name), count, transpose, v);
}

void Program::setUniformMatrix4(const GLchar* name, const GLfloat* v, GLsizei count, GLboolean transpose) {
    // assert(isInUse());
    if(hasUniform(name))
        glUniformMatrix4fv(getUniform(name), count, transpose, v);
}

void Program::setUniform(const GLchar* name, const glm::mat2& m, GLboolean transpose) {
    // assert(isInUse());
    if(hasUniform(name))
        glUniformMatrix2fv(getUniform(name), 1, transpose, glm::value_ptr(m));
}

void Program::setUniform(const GLchar* name, const glm::mat3& m, GLboolean transpose) {
    // assert(isInUse());
    if(hasUniform(name))
        glUniformMatrix3fv(getUniform(name), 1, transpose, glm::value_ptr(m));
}

void Program::setUniform(const GLchar* name, const glm::mat4& m, GLboolean transpose) {
    // assert(isInUse());
    if(hasUniform(name))
        glUniformMatrix4fv(getUniform(name), 1, transpose, glm::value_ptr(m));
}

void Program::setUniform(const GLchar* name, const glm::vec3& v) {
    // assert(isInUse());
    if(hasUniform(name))
        setUniform3v(name, glm::value_ptr(v));
}

void Program::setUniform(const GLchar* name, const glm::vec4& v) {
    // assert(isInUse());
    if(hasUniform(name))
        setUniform4v(name, glm::value_ptr(v));
}
