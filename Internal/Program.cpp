#include <stdexcept>
#include <vector>
#include "Program.h"
#include "Shader.h"

namespace Lumos{

Program::Program(std::vector<Shader> & shaders)
{
    if( shaders.size() <=0 )
        throw std::runtime_error("No Shaders loaded");

    // attach this to openGL
    _glObjId = glCreateProgram();
    if( _glObjId == 0 )
        throw std::runtime_error( "glCreateProgram Failed" );

    // testing on attaching and detaching the program and shader objects
    for ( const Shader & shader : shaders )
        glAttachShader( _glObjId, shader.getGlObjId() );

    glLinkProgram( _glObjId );

    for ( const Shader & shader: shaders )
        glDetachShader( _glObjId, shader.getGlObjId() );

    GLint status;
    glGetProgramiv( _glObjId, GL_LINK_STATUS, & status );

    // displaying log error
    if ( status == GL_FALSE ){
        std::string msg("Program/Shader linking failure: ");

        GLint infoLogLength;
        char* strInfoLog = new char[infoLogLength + 1];
        glGetProgramInfoLog( _glObjId, GL_INFO_LOG_LENGTH, nullptr, strInfoLog );
        msg += strInfoLog;
        delete[] strInfoLog;

        glDeleteProgram( _glObjId ); _glObjId = 0;
        throw std::runtime_error ( msg );

    }

}

Program::~Program(){
    if( _glObjId != 0 ) glDeleteProgram( _glObjId );
}

void Program::use() const {
    glUseProgram( _glObjId );
}

bool Program::isInUse() const {
    GLint currentProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    return (currentProgram == static_cast<GLint>( _glObjId ));
}

void Program::stopUsing() const {
    assert(isInUse());
    glUseProgram(0);
}

GLint Program::getAttrib(const GLchar* attribName) const {
    if(!attribName)
        throw std::runtime_error("attribName was NULL");

    GLint attrib = glGetAttribLocation(_glObjId, attribName);
    if(attrib == -1)
        throw std::runtime_error(std::string("Program attribute not found: ") + attribName);

    return attrib;
}



}
