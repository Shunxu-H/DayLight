
#include <algorithm> 
#include <stdexcept>

#include <Common/GL_include.h>
#include <Common/Utility.h>

#include <Lumos/Program.h>
#include <Lumos/Shader.h>
#include <Lumos/ShadingPipe.h>


using namespace Daylight::Lumos; 


void ShadingPipe::verify() const{
    Program program{};
    GLint progId = program.getObjId(); 
    use(&progId);
    glLinkProgram( program.getObjId() );

    stopUsing(&progId);
    GLint status;
    glGetProgramiv( program.getObjId(), GL_LINK_STATUS, & status );

    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    // displaying log error
    if ( status == GL_FALSE ){
        std::string msg("Program/Shader linking failure: ");

        GLint infoLogLength = 0;
        glGetProgramiv( program.getGlObjId(),
                        GL_INFO_LOG_LENGTH,
                        &infoLogLength);

        char* strInfoLog = new char[infoLogLength + 1];
        glGetProgramInfoLog( program.getObjId(), GL_INFO_LOG_LENGTH, nullptr, strInfoLog );
        msg += strInfoLog;
        delete[] strInfoLog;

        // glDeleteProgram( program.getObjId() );  
        // program.setObjId( 0 );
        throw std::runtime_error ( msg );
    }
} 

void ShadingPipe::use(void * program) const{
    auto useShaderFunc = [program](Shader shader) {shader.use(program);}; 
    std::for_each(_shaders.begin(), _shaders.end(), useShaderFunc); 
    Utils::logOpenGLError( std::string(__FUNCTION__) + ":" + std::to_string(__LINE__) );
    glLinkProgram( Utils::to<GLint>(program) );
    Utils::logOpenGLError( std::string(__FUNCTION__) + ":" + std::to_string(__LINE__) );
}

bool ShadingPipe::isInUse() const{
    size_t numOfEnabledShaders = 0; 
    std::for_each(
                _shaders.begin(), 
                _shaders.end(), 
                [&numOfEnabledShaders] (const Shader & shader) { if (shader.isInUse()) numOfEnabledShaders++;  }
    ); 
    assert (
        (numOfEnabledShaders == 0 or numOfEnabledShaders == _shaders.size())
        and "Error: Shaders status inconsistent, some shaders are enabled while others aren't"
    ); 

    return numOfEnabledShaders == _shaders.size(); 

}

void ShadingPipe::stopUsing(void * program) const{
    auto stopUseShaderFunc = [program](Shader shader) {shader.stopUsing(program);}; 
    std::for_each(_shaders.begin(), _shaders.end(), stopUseShaderFunc); 
}