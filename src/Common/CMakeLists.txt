
cmake_minimum_required(VERSION 3.0)

project(Common)

set(SOURCE  ./Utility.cpp
            ./Config.cpp
            ./Color.cpp
            )

set(HEADER  ./Extern.h
            ./GL_include.h
            ./Utility.h
            ./Config.h
            ./Color.h
)


# external dependency
# find_package(OpenGL REQUIRED)

add_library(${PROJECT_NAME} SHARED ${SOURCE} ${HEADER})
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

include_directories(${CMAKE_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})