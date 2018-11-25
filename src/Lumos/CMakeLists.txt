
cmake_minimum_required(VERSION 3.0)

project(Lumos)

set(SOURCE  ./ModelAsset.cpp
            ./Shader.cpp
            ./ArrayBuffer.cpp
            ./Texture.cpp
            ./GLObject.cpp
            ./MultisampledColorTexBuffer.cpp
            ./Program.cpp
            ./DepthTexBuffer.cpp
            ./MultisampledFrameBuffer.cpp
            ./FrameBuffer.cpp
            ./ColorTexBuffer.cpp
            ./Texture2D.cpp
            ./FrameBuffer_base.cpp
            ./MultisampledDepthTexBuffer.cpp
            ./Instance.cpp
            ./Material.cpp
            )

set(HEADER  ./DepthTexBuffer.h
            ./ColorTexBuffer.h
            ./Material.h
            ./ModelAsset.h
            ./Program.h
            ./FrameBuffer_base.h
            ./FrameBuffer.h
            ./ArrayBuffer.h
            ./MultisampledFrameBuffer.h
            ./Texture2D.h
            ./Shader.h
            ./MultisampledDepthTexBuffer.h
            ./Texture.h
            ./MultisampledColorTexBuffer.h 
)


# external dependency
# find_package(OpenGL REQUIRED)

add_library(${PROJECT_NAME} ${SOURCE} ${HEADER})
target_link_libraries(${PROJECT_NAME} 
#                         ${OPENGL_gl_LIBRARY}
                    ) 
if (APPLE)
    target_link_libraries(${PROJECT_NAME} 
        "-framework Cocoa"
        "-framework IOKit" 
        "-framework CoreVideo"
    ) 
endif()
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})