#pragma once 

#include <Lumos/ShadingPipe.h>

namespace Daylight
{
    namespace Lumos{
        class IRenderPass {
        public:
            virtual void configureShaderAndLoadResources() = 0; 
            virtual void render() = 0; 
        protected:

        private:
            ShadingPipe _shadingPipe; 
        }; 
    }
} // Daylight
