
cmake_minimum_required(VERSION 3.0)

project(Patronus)

set(SOURCE  ./Camera.cpp
            ./DirectionalLight.cpp
            ./Face.cpp
            ./Light.cpp
            ./LightFactory.cpp
            ./Mesh.cpp
            ./PhysicalWorld.cpp
            ./PointLight.cpp
            ./Shaper.cpp
            ./Transformable.cpp
            )

set(HEADER  ./Camera.h
            ./DirectionalLight.h
            ./Face.h
            ./ILight.h
            ./LightFactory.h
            ./Light.h
            ./Mesh.h
            ./PhysicalWorld.h
            ./PointLight.h
            ./Shaper.h
            ./Transformable.h
)


find_package( Bullet REQUIRED )
# external dependency
# find_package(OpenGL REQUIRED)

add_library(${PROJECT_NAME} ${SOURCE} ${HEADER})
target_link_libraries(  ${PROJECT_NAME} 
                        ${BULLET_LIBRARIES}
                        Common
#                         ${OPENGL_gl_LIBRARY}
                    ) 
if (APPLE)
    target_link_libraries(${PROJECT_NAME} 
        "-framework Cocoa"
        "-framework IOKit" 
        "-framework CoreVideo"
    ) 
endif()

include_directories(${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/libs ${GLoader_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC /usr/local/include/bullet/ )