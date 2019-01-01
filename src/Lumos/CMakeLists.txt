
cmake_minimum_required(VERSION 3.0)

project(Lumos)


find_package( Bullet REQUIRED )

set(SOURCE  ./ArrayBuffer.cpp
            ./ColorTexBuffer.cpp
            ./DepthTexBuffer.cpp
            ./FrameBuffer.cpp
            ./GLObject.cpp
            ./IFrameBuffer.cpp
            ./Instance.cpp
            ./Material.cpp
            ./ModelAsset.cpp
            ./MultisampledColorTexBuffer.cpp
            ./MultisampledDepthTexBuffer.cpp
            ./MultisampledFrameBuffer.cpp
            ./Program.cpp
            ./RenderPass/IRenderPass.cpp
            ./RenderPass/ShadowMap.cpp
            ./Shader.cpp
            ./ShadingPipe.cpp
            ./Texture2D.cpp
            ./Texture.cpp
            )

set(HEADER  ./ArrayBuffer.h
            ./ColorTexBuffer.h
            ./DepthTexBuffer.h
            ./FrameBuffer.h
            ./GLObject.h
            ./IFrameBuffer.h
            ./Instance.h
            ./Material.h
            ./ModelAsset.h
            ./MultisampledColorTexBuffer.h
            ./MultisampledDepthTexBuffer.h
            ./MultisampledFrameBuffer.h
            ./Program.h
            ./RenderPass/IRenderPass.h
            ./RenderPass/ShadowMap.h
            ./Shader.h
            ./ShadingPipe.h
            ./Texture2D.h
            ./Texture.h
)


# external dependency
find_package(OpenCV REQUIRED)



add_library(${PROJECT_NAME} ${SOURCE} ${HEADER})
target_link_libraries(  ${PROJECT_NAME} 
                        ${OpenCV_LIBS}
#                         ${OPENGL_gl_LIBRARY}
                    ) 
if (APPLE)
    target_link_libraries(${PROJECT_NAME} 
        "-framework Cocoa"
        "-framework IOKit" 
        "-framework CoreVideo"
        
    ) 
endif()


include_directories(${GLoader_SOURCE_DIR} 
                    ${OpenCV_INCLUDE_DIRS})

target_link_libraries( ${PROJECT_NAME} ${BULLET_LIBRARIES} )
link_libraries(GLoader)
link_libraries(Common)
include_directories(${CMAKE_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC /usr/local/include/bullet/ )

