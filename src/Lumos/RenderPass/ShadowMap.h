
#pragma once 

#include <string.h>

#include <Lumos/RenderPass/IRenderPass.h>
#include <Lumos/FrameBuffer.h>
#include <Lumos/Program.h>

namespace Daylight
{
    
    namespace Lumos
    {
        class ShadowMap : public IRenderPass{
        public:
            ShadowMap(const size_t & width, const size_t & height); 
            void configureShaderAndLoadResources(); 
            void render(); 

            inline size_t getWidth() const {return _frameBuffer.getWidth(); }
            inline size_t getHeight() const { return _frameBuffer.getHeight(); } 

            inline FrameBuffer getFrameBuffer() const { return _frameBuffer; }
            
        protected:
            
        private: 
            FrameBuffer _frameBuffer; 
            std::string _shadingPipeId; 
            Program _program; 
        }; 
    } // Lumos
    
} // Daylight
