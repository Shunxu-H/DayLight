#include "Instance.h"
#include "View.h"
#include "Utility.h"

#include "Extern.h"

namespace Lumos {


Instance::Instance( const glm::mat4 & modelMatrix, const ModelAsset & asset )
    :_modelMatrix(modelMatrix), _asset(asset)
{

}

void Instance::render( const View & view ) const{
    //ModelAsset* asset = inst.asset;

    gProgram->use();
    gProgram->enableShadingPipe("shader");
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
            throw std::runtime_error("undefined behavior for attributes in Instance::render()");
        }
    }

    // set unifroms
    for (const std::string & uniform: uniforms){
        switch (Utils::str2int(uniform.c_str())){
        case Utils::str2int("camera"):

            gProgram->setUniform(uniform.c_str(), view.getCamInUse()->getPerspectiveMatrix());

            break;
        case Utils::str2int("projection"):
            gProgram->setUniform(uniform.c_str(),
                      view.getCamInUse()->getProjectionMatrix(static_cast<float>(view.width())/static_cast<float>(view.height()) ));
            break;
        case Utils::str2int("model"):
            gProgram->setUniform(uniform.c_str(), glm::mat4() );
            break;
        case Utils::str2int("inverseModel"):
            gProgram->setUniform(uniform.c_str(), glm::mat4() );
            break;
        case Utils::str2int("light.position"):
            gProgram->setUniform(uniform.c_str(), shaper.getDefaultLight().getTranslate() );
            break;
        case Utils::str2int("light.intensities"):
            gProgram->setUniform(uniform.c_str(), shaper.getDefaultLight().getIntensity() );
            break;
        case Utils::str2int("ambient"):
            gProgram->setUniform(uniform.c_str(), color3(0.05f, 0.05f, 0.05f) );
            break;
        }
    }
    /*
    glm::mat4 projection = _camInUse->getProjectionMatrix(static_cast<float>(width())/static_cast<float>(height())) ;
    gProgram->setUniform("projection", projection);
    glm::mat4 pers = _camInUse->getPerspectiveMatrix();
    gProgram->setUniform("camera", pers);

    gProgram->setUniform("model", glm::mat4());
    gProgram->setUniform("inverseModel", glm::mat4());

    gProgram->setUniform("light.position", shaper.getDefaultLight().getTranslate());
    gProgram->setUniform("light.intensities", shaper.getDefaultLight().getIntensity());

    gProgram->setUniform("ambient", color3(0.05f, 0.05f, 0.05f));

    */


    glDrawArrays(_asset.drawType, _asset.drawStart, _asset.drawCount);

    //unbind everything
    //glBindVertexArray(0);
    //glBindTexture(GL_TEXTURE_2D, 0);

    //gProgram->disableShadingPipe("shader");

}
}
