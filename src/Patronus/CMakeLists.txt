
cmake_minimum_required(VERSION 3.0)

project(Patronus)

set(SOURCE  ./Transformable.cpp
            ./Shaper.cpp
            ./Mesh.cpp
            ./Light.cpp
            ./Face.cpp
            ./Camera.cpp
            ./PhysicalWorld.cpp
            )

set(HEADER  ./Transformable.h
            ./Mesh.h
            ./Light.h
            ./Face.h
            ./Camera.h
            ./Shaper.h
            ./PhysicalWorld.h
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