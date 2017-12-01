
#include <experimental/filesystem>
#include <fstream>
#include "Shader.h"
#include "GL_include.h"

#include "Extern.h"

#include <cstdio>



namespace Lumos {



const std::string Shader::default_mesh_shader_id = "multilight_shader";
const std::string Shader::depth_shader_id = "depth";
const std::string Shader::default_bbox_shader_id = "bbox_shader";
const std::string Shader::mask_shader_id = "mask";
const std::string Shader::selected_instances_shader_id = "wired_frame_shader";


Shader::Shader()
{

}

Shader::Shader(const std::string & shaderCode, const GLenum & shaderType)
    :GLObject( glCreateShader( shaderType ), 
              [](const GLuint * id){glDeleteBuffers(1, id);})
{


    if ( getObjId() == 0 )
        throw std::runtime_error( "glCreateShader failed");

    // link code
    const char * code = shaderCode.c_str();
    glShaderSource( _glObjId, 1, &code, nullptr );

    // compile
    glCompileShader( _glObjId );

    // error checking
    GLint status;
    glGetShaderiv( _glObjId , GL_COMPILE_STATUS, &status );

    if( status == GL_FALSE ){
        std::string msg("Compile failure in shader:\n");

        GLint infoLogLength;
        glGetShaderiv(getObjId(), GL_INFO_LOG_LENGTH, &infoLogLength);
        char* strInfoLog = new char[infoLogLength + 1];
        glGetShaderInfoLog(_glObjId , infoLogLength, NULL, strInfoLog);
        msg += strInfoLog;
        delete[] strInfoLog;

        glDeleteShader(getObjId()); _glObjId = 0 ;
        throw std::runtime_error(msg);
    }

}

Shader::~Shader(){
}

void Shader::getCurrentVaryingsAndUniforms(
        std::vector<std::string> & varyings, std::vector<std::string> & uniforms){

    // load attributes
    GLint i;
    GLint count;

    GLint size; // size of the variable
    GLenum type; // type of the variable (float, vec3 or mat4, etc)

    const GLsizei bufSize = 128; // maximum name length
    GLchar name[bufSize]; // variable name in GLSL
    GLsizei length; // name length
    glGetProgramiv(gProgram->getObjId(), GL_ACTIVE_ATTRIBUTES, &count);
    //printf("Active Attributes: %d\n", count);

    for (i = 0; i < count; i++)
    {
        glGetActiveAttrib(gProgram->getObjId(), i, bufSize, &length, &size, &type, name);

        //qDebug() << "Attribute " << i << "Type:" << type << " Name: " << name;
        varyings.push_back( name );
    }

    // load uniform
    glGetProgramiv(gProgram->getObjId(), GL_ACTIVE_UNIFORMS, &count);
    //printf("Active Uniforms: %d\n", count);

    for (i = 0; i < count; i++)
    {
        glGetActiveUniform(gProgram->getObjId(), (GLuint)i, bufSize, &length, &size, &type, name);

        //qDebug() << "Uniform " << i << "Type:" << type << " Name: " << name;
        uniforms.push_back( name );
    }

}

void Shader::use() const{
    glAttachShader( gProgram->getObjId(), _glObjId );
}


void Shader::stopUsing() const{
    glDetachShader( gProgram->getObjId(), _glObjId );
}

bool Shader::isInUse() const{
    throw std::runtime_error( "have not built yet" );
    /*
    void glGetAttachedShaders(	GLuint program,
    GLsizei maxCount,
    GLsizei *count,
    GLuint *shaders);
    */
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
