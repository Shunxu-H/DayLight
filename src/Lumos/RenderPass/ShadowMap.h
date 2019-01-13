
#pragma once 

#include <string.h>

#include <Lumos/RenderPass/IRenderPass.h>
#include <Lumos/DepthTexBuffer.h>

namespace Daylight
{
    
    namespace Lumos
    {
        class ShadowMap : public IRenderPass{
        public:
            ShadowMap(const size_t & width, const size_t & height) : _depthTexBuffer(width, height), _shadingPipeId("DepthMap"){}
            void configureShaderAndLoadResources(); 
            void render(); 

            inline size_t getWidth() const {return _depthTexBuffer.getWidth(); }
            inline size_t getHeight() const { return _depthTexBuffer.getHeight(); } 
        protected:
            
        private: 
            DepthTexBuffer _depthTexBuffer; 
            std::string _shadingPipeId; 

        }; 
    } // Lumos
    
} // Daylight
