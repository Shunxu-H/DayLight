
#pragma once 

#include <Lumos/RenderPass/IRenderPass.h>

namespace Daylight
{
    
    namespace Lumos
    {
        class ShadowMap : public IRenderPass{
        public:

            void configureShaderAndLoadResources(); 
            void render(); 
        protected:
            
        private: 

        }; 
    } // Lumos
    
} // Daylight
