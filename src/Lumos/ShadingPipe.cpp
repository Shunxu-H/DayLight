
#include <algorithm> 
#include <stdexcept>

#include <Common/GL_include.h>

#include <Lumos/Program.h>
#include <Lumos/Shader.h>
#include <Lumos/ShadingPipe.h>


using namespace Daylight::Lumos; 


void ShadingPipe::verify(const Program & program) const{
    use();
    isInUse(); 
    glLinkProgram( program.getObjId() );

    stopUsing();
    isInUse(); 
    GLint status;
    glGetProgramiv( program.getObjId(), GL_LINK_STATUS, & status );

    // displaying log error
    if ( status == GL_FALSE ){
        std::string msg("Program/Shader linking failure: ");

        GLint infoLogLength = 0;
        glGetProgramiv( _glObjId,
                        GL_INFO_LOG_LENGTH,
                        &infoLogLength);

        char* strInfoLog = new char[infoLogLength + 1];
        glGetProgramInfoLog( getObjId(), GL_INFO_LOG_LENGTH, nullptr, strInfoLog );
        msg += strInfoLog;
        delete[] strInfoLog;

        // glDeleteProgram( program.getObjId() );  
        // program.setObjId( 0 );
        throw std::runtime_error ( msg );

    }
} 

void ShadingPipe::use() const{
    auto useShaderFunc = [](Shader shader) {shader.use();}; 
    std::for_each(_shaders.begin(), _shaders.end(), useShaderFunc); 
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

void ShadingPipe::stopUsing() const{
    auto stopUseShaderFunc = [](Shader shader) {shader.stopUsing();}; 
    std::for_each(_shaders.begin(), _shaders.end(), stopUseShaderFunc); 
}