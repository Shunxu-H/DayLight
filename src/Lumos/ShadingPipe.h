#pragma once 

#include <Lumos/GLObject.h>
#include <Lumos/Shader.h>
#include <vector>


/***
 * Store a valid list of shader objects, when enabled, 
 * it forms a complete set of self contained rendering
 * object 
 **/

namespace Daylight
{

    namespace Lumos
    {

        class ShadingPipe: public GLObject{
        public:
            inline ShadingPipe(){};
            // ShadingPipe(const ShaingPipe & that) = default; 
            inline ShadingPipe( std::vector<Shader> shaders ): _shaders(shaders) {}
            
            inline void addShader(Shader shader) { _shaders.push_back(shader); }

            void verify(const Program & program) const; 

            void use() const;
            bool isInUse() const;
            void stopUsing() const;
        protected:

        private:
            std::vector<Shader> _shaders; 
            

        };     
    } // Lumos
    
} // Daylight
