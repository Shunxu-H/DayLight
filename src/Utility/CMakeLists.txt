
cmake_minimum_required(VERSION 3.0)

project(Utility)

set(SOURCE  ./Color.cpp
            ./Utility.cpp
            ./Config.cpp
            ./InputParser.cpp
            )

set(HEADER  ./Utility.h
            ./InputParser.h
            ./Config.h
            ./Color.h
            ./Func.h
)


# external dependency
# find_package(OpenGL REQUIRED)

add_library(${PROJECT_NAME} ${SOURCE} ${HEADER})
target_link_libraries(${PROJECT_NAME} 
#                         ${OPENGL_gl_LIBRARY}
                    ) 
# if (APPLE)
#     target_link_libraries(${PROJECT_NAME} 
#         "-framework Cocoa"
#         "-framework IOKit" 
#         "-framework CoreVideo"
#     ) 
# endif()
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})