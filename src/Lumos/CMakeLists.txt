
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
            ./CopyFile.cmake
            )

set(HEADER  ./DepthTexBuffer.h
            ./RenderPass/ShadowMap.h
            ./RenderPass/IRenderPass.h
            ./ColorTexBuffer.h
            ./Instance.h
            ./Material.h
            ./ShadingPipe.h
            ./ModelAsset.h
            ./Program.h
            ./GLObject.h
            ./FrameBuffer.h
            ./ArrayBuffer.h
            ./MultisampledFrameBuffer.h
            ./Texture2D.h
            ./Shader.h
            ./IFrameBuffer.h
            ./GlslNameConst.h
            ./MultisampledDepthTexBuffer.h
            ./Texture.h
            ./MultisampledColorTexBuffer.h
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

# copy files
ADD_CUSTOM_TARGET(
        copy_shader_files
        ${CMAKE_COMMAND}
        # WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        -D SOURCE_DIR=${CMAKE_SOURCE_DIR}
        -D DESTINATION_DIR=${CMAKE_RUNTIME_OUTPUT_DIRECTORY} 
        -P ${CMAKE_CURRENT_SOURCE_DIR}/CopyFile.cmake
        COMMENT "Copying Files for target: test_SphereShader" VERBATIM 
        )

ADD_DEPENDENCIES ( ${PROJECT_NAME} copy_shader_files )