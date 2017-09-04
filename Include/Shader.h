#ifndef SHADER_H
	#define SHADER_H

#include <vector>
#include <string>
#include <memory>
#include <GL/gl.h>
#include <glm/vec3.hpp>
#include "Object.h"
#include "GLObject.h"
#include "Countable.h"
#include "Edge.h"
#include "Vector.h"

class Coordinate;
class Geometry;
namespace Lumos {

    class Shader : public GLObject, public Countable
    {
    public:
        Shader( const std::string& file="./data/cube.obj" );
        virtual ~Shader();
        virtual void bind () const{}

        /**
         * @brief readFromFile, creat a shader from file
         * @param filePath, path to the shader file
         * @param shaderType,
         * @return the constructed shader
         */
        static Shader readFromFile(const std::string & filePath, const GLenum & shaderType );
        /**
         * @brief readFromFiles, construct a vector of shader using the shader files in @shaderDir
         * @param shaderDir, path to the directory where shader files are stored
         * @return a vector of shader
         */
        static std::vector<Shader> readFromFiles( const std::string & shaderDir );

        void addObj(std::shared_ptr<Object> newObj );
        void clear();
        void save(const std::string& fileName);
        std::shared_ptr<Object> getCurSelection()const;
        void deleteObj(Object const* g);
        void print()const;
        Vector getColor(const Vector& v, const Vector & normal)const;

        inline unsigned int size()const{ return objects.size(); }
        Edge rotationVector;

        // float getMaxX()const;
        // float getMinX()const;
        // float getMaxY()const;
        // float getMinY()const;
        // float getMaxZ()const;
        // float getMinZ()const;
        int geoGetN(const Object* geoPtr)const;
        std::shared_ptr<Object> nGetGeo(const unsigned int &index)const;
        void loadFile (const std::string& _fileName="");
        void drawAll();
        float getColorNormalizeRate()const;

        void normalizeColors(const float& colorRate )const;

        void drawLight()const;
        void moveLight(const Vector& newPos);

        void moveView(const Vector& newPos);
        bool isSelected( Object const * toCheck )const{ return curSelection.get() == toCheck;}
        void shiftSelectionUp();
        void shiftSelectionDown();
        void insert(std::shared_ptr<Vector> v);

        void push_front(std::shared_ptr<Vector> v);
        void push_back(std::shared_ptr<Vector> v);

        void selectVertices(const Vector & v1, const Vector & v2);
        void deleteVertices();


        void setK(const int & k);
        void setUVector(const std::vector<float> & us);
        void setOneU(const int & index, const float & value);
        void toggleCurveType();
        void setResolution(const int & res);

        Vector phong(const Vector& p, const Vector &viewPtr, const std::shared_ptr<const Object> & obj, const unsigned int & levelLeft)const;


        Vector rayTrace(const Line & view)const;
        Vector translateFromWorldToViewPort(Vector v)const{}

        std::pair<Vector, std::shared_ptr<const Object>> getIntersection(const Line & view)const;
        bool isCasted(const Vector & light, const Vector & p)const;
    protected:


    private:
        /**
         * @brief Shader
         * @param filePath file path to the GLSL file
         * @param shaderType type of shader
         *        must be
         *        GL_COMPUTE_SHADER | GL_VERTEX_SHADER |
         *        GL_TESS_CONTROL_SHADER | GL_TESS_EVALUATION_SHADER |
         *        GL_GEOMETRY_SHADER | GL_FRAGMENT_SHADER
         */
        Shader(const std::string & filePath, const GLenum & shaderType );

        void _glCleanUp();

        std::string fileName;
        std::vector<std::shared_ptr<Object>> objects;
        Vector viewPtr;
        Vector lightSource;
        std::shared_ptr<Object> curRendering;
        Vector getNormalVector(const Vector& v)const;
        std::shared_ptr<Object> curSelection;

        std::vector<glm::vec3> vertices;
        //function
        bool loadFile_obj(const std::string &);


    };

}

	#endif
