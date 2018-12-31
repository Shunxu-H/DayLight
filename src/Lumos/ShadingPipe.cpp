
#include <algorithm> 
#include <stdexcept>

#include <Common/GL_include.h>

#include <Lumos/Program.h>
#include <Lumos/Shader.h>
#include <Lumos/ShadingPipe.h>


using namespace Daylight::Lumos; 


void ShadingPipe::verify(const Program & program) const{
    use();
        
    glLinkProgram( program.getObjId() );

    stopUsing();
    
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
    assert (
        not (std::all_of(_shaders.begin(), _shaders.end(), 
        [](Shader shader){ return shader.isInUse(); }) 
        or 
        std::all_of(_shaders.begin(), _shaders.end(), 
        [](Shader shader){ return !shader.isInUse(); }) 
        )
        and 
        "Shader inUse status inconsistent (some are in used while others are not"
        ); 
    return std::all_of(_shaders.begin(), _shaders.end(), 
        [](Shader shader){ return shader.isInUse();});

}

void ShadingPipe::stopUsing() const{
    auto stopUseShaderFunc = [](Shader shader) {shader.stopUsing();}; 
    std::for_each(_shaders.begin(), _shaders.end(), stopUseShaderFunc); 
}