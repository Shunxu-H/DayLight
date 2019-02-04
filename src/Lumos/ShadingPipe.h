#pragma once 

#include <Lumos/GLObject.h>
#include <Lumos/Shader.h>
#include <vector>

/**
 * @brief and shading pipe object contains a list of openGL shader objects, 
 * which consist of a complete opengl graphics pipeline
 * 
 */

namespace Daylight
{

    namespace Lumos
    {

        class ShadingPipe{
        public:
            inline ShadingPipe(){};
            // ShadingPipe(const ShaingPipe & that) = default; 
            inline ShadingPipe( std::vector<Shader> shaders ): _shaders(shaders) {}
            
            inline void addShader(Shader shader) { _shaders.push_back(shader); }

            /**
             * @brief verify if openGL can compile the shaders attached to the shading pipe,
             *  throw error is not compiled 
             */
            void verify() const; 

            /**
             * @brief enable the shading pipe 
             * 
             */
            void use(void * program) const;

            /**
             * @brief it verifies all shaders are enabled or disabled, 
             * throw error if some shaders are enabled while others are 
             * not
             * 
             * @return true all shaders are enabled 
             * @return false all ahders are disabled
             */
            bool isInUse() const;

            /**
             * @brief disable all shaders attahed to the shading pipe
             * 
             */
            void stopUsing(void * program) const;
        protected:

        private:
            std::vector<Shader> _shaders; 
            

        };     
    } // Lumos
    
} // Daylight
