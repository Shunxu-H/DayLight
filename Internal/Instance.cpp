#include <QDebug>
#include "Instance.h"
#include "View.h"
#include "Utility.h"

#include "Extern.h"

namespace Lumos {


Instance::Instance( Patronus::Mesh * meshPtr, const ModelAsset & asset)
    :_meshPtr(meshPtr), _asset(asset), _rigidBody( nullptr )
{

}

Instance::~Instance(){
    //if (_rigidBody) delete _rigidBody;
}

void Instance::loadAttribsAndUniform( const View & view ) const {
    // bind VAO
    glBindVertexArray(_asset.VAO);
    std::vector<std::string> attribs;
    std::vector<std::string> uniforms;
    GLuint attribId;
    Shader::getCurrentVaryingsAndUniforms(attribs, uniforms);


    point3 data[6];
    // load attributes
    for (const std::string & attrib: attribs){
        switch (Utils::str2int(attrib.c_str())){
        case Utils::str2int("vert"):
            attribId = gProgram->getAttrib(attrib.c_str());
            glBindBuffer(GL_ARRAY_BUFFER, _asset.VBO_VERT);

            glGetBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(point3)*6, data);

            glEnableVertexAttribArray(attribId);
            glVertexAttribPointer(attribId, 3, GL_FLOAT, GL_FALSE, 0, 0);
            break;
        case Utils::str2int("vertNormal"):

            attribId = gProgram->getAttrib(attrib.c_str());
            glBindBuffer(GL_ARRAY_BUFFER, _asset.VBO_NORMAL);
            glEnableVertexAttribArray(attribId);
            glVertexAttribPointer(attribId, 3, GL_FLOAT, GL_FALSE, 0, 0);
            break;
        default:
            throw std::runtime_error("##in Instance::render()## Undefined Attribute: " + attrib);
        }
    }

    bool hasAllLight = false;
    // set unifroms
    for (const std::string & uniform: uniforms){
        if( uniform.compare("camera") == 0)
            gProgram->setUniform(uniform.c_str(), view.getCamInUse()->getPerspectiveMatrix());
        else if( uniform.compare("cameraPosition") == 0)
            gProgram->setUniform(uniform.c_str(), view.getCamInUse()->getTranslate());
        else if( uniform.compare("projection") == 0)
            gProgram->setUniform(uniform.c_str(),
                      view.getCamInUse()->getProjectionMatrix(static_cast<float>(view.width())/static_cast<float>(view.height()) ));
        else if( uniform.compare("model") == 0)
            gProgram->setUniform(uniform.c_str(), getModelMatrix() );
        else if( uniform.compare("inverseModel") == 0)
            gProgram->setUniform(uniform.c_str(), getInverseModelMatrix() );
        else if( uniform.compare("light.position") == 0)
            gProgram->setUniform(uniform.c_str(), shaper.getDefaultLight().getTranslate() );
        else if( uniform.compare("light.intensities") == 0)
            gProgram->setUniform(uniform.c_str(), shaper.getDefaultLight().getIntensity() );
        else if( uniform.compare("ambient") == 0)
            gProgram->setUniform(uniform.c_str(), color3(0.05f, 0.05f, 0.05f) );
        else if( uniform.compare("materialShininess") == 0)
            gProgram->setUniform(uniform.c_str(), _asset.material->reflexitivity );
        else if( uniform.compare("materialSpecularColor") == 0)
            gProgram->setUniform(uniform.c_str(), color3 (1.0f, 1.0f, 1.0f));
        else if( uniform.compare("numLights") == 0)
            gProgram->setUniform(uniform.c_str(), (int)shaper.getLights().size());
        else if( uniform.compare("ModelViewProjectionMatrix") == 0)
            gProgram->setUniform(uniform.c_str(),
                                 view.getCamInUse()->getProjectionMatrix(static_cast<float>(view.width())/static_cast<float>(view.height()) )*
                                 view.getCamInUse()->getPerspectiveMatrix()*
                                 getModelMatrix());
        else if( uniform.substr(0, 9).compare("allLights") == 0 )
            //gProgram->setUniform(uniform.c_str(), glm::vec3(1.0f, 1.0f, 1.0f));
            hasAllLight = true;
            //qDebug() << (uniform.compare("allLights[0].position") == 0);
        else
            throw std::runtime_error( "##in Instance::render()## Undefined Uniform: " + uniform);
    }

    if ( hasAllLight ){

        size_t i = 0;
        for ( const Patronus::Light & l : shaper.getLights() ){

            gProgram->SetLightUniform("isDirectional", i, l.getType() == Patronus::LightType::DIRECTIONAL);
            gProgram->SetLightUniform("position", i, l.getTranslatev4());
            gProgram->SetLightUniform("intensities", i, l.getIntensity());
            gProgram->SetLightUniform("attenuation", i, l.getAttenuation());
            gProgram->SetLightUniform("ambientCoefficient", i, l.getAmbientCoefficient());
            gProgram->SetLightUniform("coneAngle", i, l.getConeAngle());
            gProgram->SetLightUniform("coneDirection", i, l.getConeDirection());
            i++;
        }
    }
}

void Instance::renderMesh( const View & view ) const{


    loadAttribsAndUniform( view );

    glDrawArrays(_asset.drawType, _asset.drawStart, _asset.drawCount);

    //unbind everything
    //glBindTexture(GL_TEXTURE_2D, 0);

    glBindVertexArray(0);

}


void Instance::renderBoundngBox( const View & view ) const{
    //gProgram->use();

    loadAttribsAndUniform( view );

    //glDrawArrays(_asset.drawType, _asset.drawStart, _asset.drawCount);




    // Cube 1x1x1, centered on origin
    GLfloat vertices[] = {
        -0.5, -0.5, -0.5,
         0.5, -0.5, -0.5,
         0.5,  0.5, -0.5,
        -0.5,  0.5, -0.5,
        -0.5, -0.5,  0.5,
         0.5, -0.5,  0.5,
         0.5,  0.5,  0.5,
        -0.5,  0.5,  0.5,
    };
    GLuint vbo_vertices;
    glGenBuffers(1, &vbo_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLushort elements[] = {
        0, 1, 2, 3,
        4, 5, 6, 7,
        0, 4, 1, 5, 2, 6, 3, 7
    };
    GLuint ibo_elements;
    glGenBuffers(1, &ibo_elements);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    glm::vec3 min = _meshPtr->getMinPos();
    glm::vec3 max = _meshPtr->getMaxPos();

    glm::vec3 size = glm::vec3(max.x-min.x, max.y-min.y, max.z-min.z);
    glm::vec3 center = glm::vec3((min.x+max.x)/2, (min.y+max.y)/2, (min.z+max.z)/2);
    glm::mat4 transform =  glm::translate(glm::mat4(1), center)* glm::scale(glm::mat4(1), size);

    gProgram->setUniform("ModelViewProjectionMatrix",
                         view.getCamInUse()->getProjectionMatrix(static_cast<float>(view.width())/static_cast<float>(view.height()) )*
                         view.getCamInUse()->getPerspectiveMatrix()*
                         getModelMatrix()*
                         transform);

    //glm::mat4 m = _meshPtr->getModelMatrix() * transform;
    //glUniformMatrix4fv(uniform_m, 1, GL_FALSE, glm::value_ptr(m));

    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glEnableVertexAttribArray(gProgram->getAttrib("vert"));
    glVertexAttribPointer(
    gProgram->getAttrib("vert"),  // attribute
        3,                  // number of elements per vertex, here (x,y,z,w)
        GL_FLOAT,           // the type of each element
        GL_FALSE,           // take our values as-is
        0,                  // no extra data between each position
        0                   // offset of first element
    );


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
    glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, 0);
    glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, (GLvoid*)(4*sizeof(GLushort)));
    glDrawElements(GL_LINES, 8, GL_UNSIGNED_SHORT, (GLvoid*)(8*sizeof(GLushort)));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //glDisableVertexAttribArray(attribute_v_coord);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &vbo_vertices);
    glDeleteBuffers(1, &ibo_elements);



}

}
