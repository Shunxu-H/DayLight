
cmake_minimum_required(VERSION 3.0)

project(Lumos)


find_package( Bullet REQUIRED )

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
            ./Instance.h
            ./Material.h
            ./ModelAsset.h
            ./Program.h
            ./GLObject.h
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


include_directories(${GLoader_SOURCE_DIR})

target_link_libraries( ${PROJECT_NAME} ${BULLET_LIBRARIES} )
link_libraries(GLoader)
link_libraries(Common)
include_directories(${CMAKE_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC /usr/local/include/bullet/ )

