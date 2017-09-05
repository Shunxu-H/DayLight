
#include <experimental/filesystem>
#include <fstream>
#include "Shader.h"
#include "GL_include.h"

#include "Extern.h"





namespace Lumos {





Shader::Shader(const std::string & shaderCode, const GLenum & shaderType){
    setObjId( glCreateShader( shaderType ) );

    if ( getObjId() == 0 )
        throw std::runtime_error( "glCreateShader failed");

    // link code
    const char * code = shaderCode.c_str();
    glShaderSource( getObjId(), 1, &code, nullptr );

    // compile
    glCompileShader( getObjId() );

    // error checking
    GLint status;
    glGetShaderiv( getObjId(), GL_COMPILE_STATUS, &status );

    if( status == GL_FALSE ){
        std::string msg("Compile failure in shader:\n");

        GLint infoLogLength;
        glGetShaderiv(getObjId(), GL_INFO_LOG_LENGTH, &infoLogLength);
        char* strInfoLog = new char[infoLogLength + 1];
        glGetShaderInfoLog(getObjId(), infoLogLength, NULL, strInfoLog);
        msg += strInfoLog;
        delete[] strInfoLog;

        glDeleteShader(getObjId()); setObjId( 0 );
        throw std::runtime_error(msg);
    }

}

Shader::~Shader(){
    if (*_refCount == 1){
        glDeleteShader( getObjId() );
        setObjId( 0 );
    }
}


Shader Shader::readFromFile(const std::string & fileName, const GLenum & shaderType ){
    std::ifstream f (fileName.c_str());

    if( !f.is_open() ){
        throw std::runtime_error( "Failed to open shader file: " + fileName  );
    }

    std::stringstream buffer;
    buffer << f.rdbuf();

    // construct shader and return
    return Shader(buffer.str(), shaderType);

}


std::vector<Shader> Shader::readFromFiles( const std::string & shaderDir ){
    std::vector<Lumos::Shader> shaders;

    {
        namespace fs = std::experimental::filesystem;

        for (const auto & p : fs::directory_iterator(shaderDir))
        {

            //std::cout << fs::path(p).extension() << std::endl;
            if ( std::string( fs::path(p).extension() ).compare(".vert") == 0 )
                shaders.push_back(Shader::readFromFile( fs::path( p ), GL_VERTEX_SHADER ));
            else if ( std::string( fs::path(p).extension() ).compare(".frag") == 0 )
                shaders.push_back(Shader::readFromFile( fs::path( p ), GL_FRAGMENT_SHADER ));
        }

    }

    return shaders;
}



}
