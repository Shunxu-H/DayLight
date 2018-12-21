
cmake_minimum_required(VERSION 3.0)

project(Common)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -fPIC")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -fPIC")

set(SOURCE  ./Utility.cpp
            ./Config.cpp
            ./Color.cpp
            )

set(HEADER  ./Exception.h
            ./GlResource.h
            ./Utility.h
            ./Config.h
            ./Extern.h
            ./GL_include.h
            ./Color.h
)


# external dependency
# find_package(OpenGL REQUIRED)

add_library(${PROJECT_NAME} SHARED ${SOURCE} ${HEADER})
target_link_libraries(  ${PROJECT_NAME} 
                        GLoader
                    ) 
if (APPLE)
    target_link_libraries(${PROJECT_NAME} 
        "-framework Cocoa"
        "-framework IOKit" 
        "-framework CoreVideo"
    ) 
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
            CXX_STANDARD 17
            CXX_EXTENSIONS OFF
            )


include_directories(${CMAKE_SOURCE_DIR}/src ${GLoader_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})