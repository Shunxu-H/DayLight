#include "Instance.h"
#include "View.h"
#include "Utility.h"

#include "Extern.h"

namespace Lumos {


Instance::Instance( Patronus::Mesh * meshPtr, const ModelAsset & asset)
    :_meshPtr(meshPtr), _asset(asset), _rigidBody( nullptr )
{

}

//Instance::~Instance(){
//    //if (_rigidBody) delete _rigidBody;
//}

void Instance::setRidgidBody(  btRigidBody * const &  arg )
{
    if(_rigidBody){
        world->getWorld()->removeRigidBody(_rigidBody);
        delete _rigidBody->getMotionState();
        delete _rigidBody;
    }
    arg->setUserPointer(this);
    _rigidBody = arg;
}


void Instance::loadAttribsAndUniform() const {

    GLuint attribId;
    if (gProgram->hasAttribute("vert")){
        attribId = gProgram->getAttrib("vert");
        glBindBuffer(GL_ARRAY_BUFFER, _asset.VBO_VERT);

        Utils::logOpenGLError();
        glEnableVertexAttribArray(attribId);
        Utils::logOpenGLError();
        glVertexAttribPointer(attribId, 3, GL_FLOAT, GL_FALSE, 0, 0);
        Utils::logOpenGLError();
    }
    if (gProgram->hasAttribute("vertNormal")){
        attribId = gProgram->getAttrib("vertNormal");
        glBindBuffer(GL_ARRAY_BUFFER, _asset.VBO_NORMAL);
        glEnableVertexAttribArray(attribId);
        glVertexAttribPointer(attribId, 3, GL_FLOAT, GL_FALSE, 0, 0);
        Utils::logOpenGLError();
    }
    if (gProgram->hasAttribute("vertTexCoord")){
        attribId = gProgram->getAttrib("vertTexCoord");
        glBindBuffer(GL_ARRAY_BUFFER, _asset.VBO_TEXCOORD);
        glEnableVertexAttribArray(attribId);
        glVertexAttribPointer(attribId, 2, GL_FLOAT, GL_FALSE, 0, 0);
        Utils::logOpenGLError();
    }

    // load uniform
    if( gProgram->hasUniform("inverseModel") )
        gProgram->setUniform( "inverseModel" , getInverseModelMatrix() );
    Utils::logOpenGLError();

    if( gProgram->hasUniform("model") )
        gProgram->setUniform("model", getModelMatrix() );

    if( gProgram->hasUniform("pickingColor") )
        gProgram->setUniform("pickingColor", getPickingColor() );


    Utils::logOpenGLError();
}

void Instance::renderMesh( Material * materialInUse ) const{


    for (const MaterialPack & mp: _asset.materials ){
        if (materialInUse != mp.material ){
            
            Utils::logOpenGLError();
            mp.material->loadUniforms();
            Utils::logOpenGLError();
            materialInUse = mp.material;
        }
        loadAttribsAndUniform( );
        Utils::logOpenGLError();
        glDrawArrays(_asset.drawType, mp.drawStart, mp.drawCnt);
        Utils::logOpenGLError();
    }


}


void Instance::renderMeshToTexture( Material * materialInUse ) const{
    for (const MaterialPack & mp: _asset.materials ){
        if (materialInUse != mp.material ){
            mp.material->loadUniforms();
            materialInUse = mp.material;
        }
        loadAttribsAndUniform( );
        glDrawArrays(_asset.drawType, mp.drawStart, mp.drawCnt);
    }
}

void Instance::renderMesh_indexed( const View & view ) const{


    // loadAttribsAndUniform( view );

    // glDrawArrays(_asset.drawType, _asset.drawStart, _asset.drawCount);

    glBindVertexArray(0);

}


void Instance::renderBoundngBox( const View & view ) const{
    //gProgram->use();

    //loadAttribsAndUniform( Patronus::Shaper::default_material );

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
                         view.getCamInUse()->getProjectionMatrix(static_cast<float>(view.getWidth())/static_cast<float>(view.getHeight()) )*
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
