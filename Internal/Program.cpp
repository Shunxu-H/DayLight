#include <stdexcept>
#include <vector>
#include <experimental/filesystem>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Program.h"
#include "Shader.h"
#include "ArrayBuffer.h"

#include "Extern.h"

namespace Lumos{

Program::Program(std::vector<Shader> shaders)
{
    if( shaders.size() <=0 )
        throw std::runtime_error("No Shaders loaded");

    // attach this to openGL
    setObjId( glCreateProgram() );
    if( getObjId() == 0 )
        throw std::runtime_error( "glCreateProgram Failed" );

    // testing on attaching and detaching the program and shader objects
    for ( const Shader & shader : shaders )
        glAttachShader( getObjId(), shader.getGlObjId() );

    glLinkProgram( getObjId() );

    for ( const Shader & shader: shaders )
        glDetachShader( getObjId(), shader.getGlObjId() );

    GLint status;
    glGetProgramiv( getObjId(), GL_LINK_STATUS, & status );

    // displaying log error
    if ( status == GL_FALSE ){
        std::string msg("Program/Shader linking failure: ");

        GLint infoLogLength;
        char* strInfoLog = new char[infoLogLength + 1];
        glGetProgramInfoLog( getObjId(), GL_INFO_LOG_LENGTH, nullptr, strInfoLog );
        msg += strInfoLog;
        delete[] strInfoLog;

        glDeleteProgram( getObjId() );  setObjId( 0 );
        throw std::runtime_error ( msg );

    }
    _shaders = shaders;

}

void Program::preDrawSetUp() {
    gProgram->use();
    gProgram->attachAllShaders();

    GLsizei count;
    GLuint shaderName[3];
    glGetAttachedShaders(	gProgram->getObjId(),
        3,
        &count,
        shaderName);
    /*

    _curVAO = shaper.getBuffer();
    glBindVertexArray( _curVAO );


    // make and bind the VBO
    glGenBuffers(1, &_curVBO);
    glBindBuffer(GL_ARRAY_BUFFER, _curVBO);


    // connect the xyz to the "vert" attribute of the vertex shader
    glEnableVertexAttribArray(gProgram->getAttrib("vert"));
    glVertexAttribPointer(gProgram->getAttrib("vert"),4 , GL_FLOAT, GL_FALSE, 0, NULL);
    */
    // make and bind the VAO
/*
        _curVAO = shaper.getBuffer();
        glBindVertexArray( _curVAO );



        //glm::mat4 projection = glm::perspective(glm::radians(50.0f), width()/SCREEN_SIZE.y, 0.1f, 10.0f);
        // make and bind the VBO
        glGenBuffers(1, &_curVBO);
        glBindBuffer(GL_ARRAY_BUFFER, _curVBO);

        // Put the three triangle verticies into the VBO
        GLfloat vertexData[] = {
            //  X     Y     Z
             0.0f, 0.8f, 0.0f, 1.0,
            -0.8f,-0.8f, 0.0f, 1.0,
             0.8f,-0.8f, 0.0f, 1.0
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

        // connect the xyz to the "vert" attribute of the vertex shader
        glEnableVertexAttribArray(gProgram->getAttrib("vert"));
        glVertexAttribPointer(gProgram->getAttrib("vert"), 4, GL_FLOAT, GL_FALSE, 0, NULL);

        // unbind the VBO and VAO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);


        glClearColor(0, 0, 0, 1); // black
        glClear(GL_COLOR_BUFFER_BIT);

        // bind the program (the shaders)
        glUseProgram(gProgram->getGlObjId());

        // bind the VAO (the triangle)
        glBindVertexArray(_curVAO);
        */
    // make and bind the VAO
        // make and bind the VBO
        glGenVertexArrays(1, &_curVAO);
        glBindVertexArray( _curVAO );


    _curVBO = shaper.getBuffer();
    glBindBuffer(GL_ARRAY_BUFFER, _curVBO.getGlObjId());



        //glBufferData(GL_ARRAY_BUFFER, sizeof(point4)*shaper.getNumOfVertices(), vertexData, GL_STATIC_DRAW);

        // connect the xyz to the "vert" attribute of the vertex shader
        GLuint vert = gProgram->getAttrib("vert");

        //glVertexAttribPointer(gProgram->getAttrib("vert"), 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), NULL);
        glEnableVertexAttribArray(vert);
        glVertexAttribPointer(vert, 4, GL_FLOAT, GL_FALSE, 0, 0);

        // connect the uv coords to the "vertTexCoord" attribute of the vertex shader
        //glEnableVertexAttribArray(gProgram->getAttrib("vertTexCoord"));
        //glVertexAttribPointer(gProgram->getAttrib("vertTexCoord"), 2, GL_FLOAT, GL_TRUE,  5*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));

        // unbind the VAO
        //glBindVertexArray(0);

}

Program::~Program(){
    if( getObjId() != 0 )
        glDeleteProgram( getObjId() );
}

void Program::use() const {
    glUseProgram( getObjId() );
}

bool Program::isInUse() const {
    GLint currentProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    return (currentProgram == static_cast<GLint>( getObjId() ));
}

void Program::stopUsing() const {
    assert(isInUse());
    glUseProgram(0);
}

void Program::bind() const{
    glLinkProgram( getObjId() );
}


void Program::attachAllShaders() const {
    for ( const Shader & shader : _shaders )
        glAttachShader( getObjId(), shader.getGlObjId() );
}

void Program::detachAllShaders() const {
    for ( const Shader & shader: _shaders )
        glDetachShader( getObjId(), shader.getGlObjId() );
}

GLint Program::getAttrib(const GLchar* attribName) const {
    if(!attribName)
        throw std::runtime_error("attribName was NULL");

    GLint attrib = glGetAttribLocation( getObjId(), attribName );
    if(attrib == -1)
        throw std::runtime_error(std::string("Program attribute not found: ") + attribName);

    return attrib;
}


GLint Program::getUniform(const GLchar* uniformName) const {
    if(!uniformName)
        throw std::runtime_error("uniformName was NULL");

    GLint uniform = glGetUniformLocation( getObjId(), uniformName );
    if(uniform == -1)
        throw std::runtime_error(std::string("Program uniform not found: ") + uniformName);

    return uniform;
}

#define ATTRIB_N_UNIFORM_SETTERS(OGL_TYPE, TYPE_PREFIX, TYPE_SUFFIX) \
\
    void Program::setAttrib(const GLchar* name, OGL_TYPE v0) \
        { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 1 ## TYPE_SUFFIX (getAttrib(name), v0); } \
    void Program::setAttrib(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1) \
        { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 2 ## TYPE_SUFFIX (getAttrib(name), v0, v1); } \
    void Program::setAttrib(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2) \
        { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 3 ## TYPE_SUFFIX (getAttrib(name), v0, v1, v2); } \
    void Program::setAttrib(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3) \
        { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 4 ## TYPE_SUFFIX (getAttrib(name), v0, v1, v2, v3); } \
\
    void Program::setAttrib1v(const GLchar* name, const OGL_TYPE* v) \
        { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 1 ## TYPE_SUFFIX ## v (getAttrib(name), v); } \
    void Program::setAttrib2v(const GLchar* name, const OGL_TYPE* v) \
        { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 2 ## TYPE_SUFFIX ## v (getAttrib(name), v); } \
    void Program::setAttrib3v(const GLchar* name, const OGL_TYPE* v) \
        { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 3 ## TYPE_SUFFIX ## v (getAttrib(name), v); } \
    void Program::setAttrib4v(const GLchar* name, const OGL_TYPE* v) \
        { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 4 ## TYPE_SUFFIX ## v (getAttrib(name), v); } \
\
    void Program::setUniform(const GLchar* name, OGL_TYPE v0) \
        { assert(isInUse()); glUniform1 ## TYPE_SUFFIX (getUniform(name), v0); } \
    void Program::setUniform(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1) \
        { assert(isInUse()); glUniform2 ## TYPE_SUFFIX (getUniform(name), v0, v1); } \
    void Program::setUniform(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2) \
        { assert(isInUse()); glUniform3 ## TYPE_SUFFIX (getUniform(name), v0, v1, v2); } \
    void Program::setUniform(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3) \
        { assert(isInUse()); glUniform4 ## TYPE_SUFFIX (getUniform(name), v0, v1, v2, v3); } \
\
    void Program::setUniform1v(const GLchar* name, const OGL_TYPE* v, GLsizei count) \
        { assert(isInUse()); glUniform1 ## TYPE_SUFFIX ## v (getUniform(name), count, v); } \
    void Program::setUniform2v(const GLchar* name, const OGL_TYPE* v, GLsizei count) \
        { assert(isInUse()); glUniform2 ## TYPE_SUFFIX ## v (getUniform(name), count, v); } \
    void Program::setUniform3v(const GLchar* name, const OGL_TYPE* v, GLsizei count) \
        { assert(isInUse()); glUniform3 ## TYPE_SUFFIX ## v (getUniform(name), count, v); } \
    void Program::setUniform4v(const GLchar* name, const OGL_TYPE* v, GLsizei count) \
        { assert(isInUse()); glUniform4 ## TYPE_SUFFIX ## v (getUniform(name), count, v); }


ATTRIB_N_UNIFORM_SETTERS(GLfloat, , f);
ATTRIB_N_UNIFORM_SETTERS(GLint, I, i);
ATTRIB_N_UNIFORM_SETTERS(GLuint, I, ui);

void Program::setUniformMatrix2(const GLchar* name, const GLfloat* v, GLsizei count, GLboolean transpose) {
    assert(isInUse());
    glUniformMatrix2fv(getUniform(name), count, transpose, v);
}

void Program::setUniformMatrix3(const GLchar* name, const GLfloat* v, GLsizei count, GLboolean transpose) {
    assert(isInUse());
    glUniformMatrix3fv(getUniform(name), count, transpose, v);
}

void Program::setUniformMatrix4(const GLchar* name, const GLfloat* v, GLsizei count, GLboolean transpose) {
    assert(isInUse());
    glUniformMatrix4fv(getUniform(name), count, transpose, v);
}

void Program::setUniform(const GLchar* name, const glm::mat2& m, GLboolean transpose) {
    assert(isInUse());
    glUniformMatrix2fv(getUniform(name), 1, transpose, glm::value_ptr(m));
}

void Program::setUniform(const GLchar* name, const glm::mat3& m, GLboolean transpose) {
    assert(isInUse());
    glUniformMatrix3fv(getUniform(name), 1, transpose, glm::value_ptr(m));
}

void Program::setUniform(const GLchar* name, const glm::mat4& m, GLboolean transpose) {
    assert(isInUse());
    glUniformMatrix4fv(getUniform(name), 1, transpose, glm::value_ptr(m));
}

void Program::setUniform(const GLchar* uniformName, const glm::vec3& v) {
    setUniform3v(uniformName, glm::value_ptr(v));
}

void Program::setUniform(const GLchar* uniformName, const glm::vec4& v) {
    setUniform4v(uniformName, glm::value_ptr(v));
}


}
