
cmake_minimum_required(VERSION 3.0)

project(GLoader)



# external dependency
find_package(OpenGL REQUIRED)

# if(APPLE)
#   set(GL3W_SOURCE 
#         ./gl3w/MacOS/gl3w.c)
# endif()

set(SOURCE  ./gl3w/gl3w.c
            ./usynergy/uSynergy.c
            )
            
set(HEADER  ./gl3w/glcorearb.h
            ./gl3w/gl3w.h
            ./glfw/include/GLFW/glfw3.h
            ./glfw/include/GLFW/glfw3native.h
            ./usynergy/uSynergy.h
)


add_library(${PROJECT_NAME} ${SOURCE} ${HEADER})
target_compile_options(${PROJECT_NAME} PUBLIC -fPIC)
target_include_directories(${PROJECT_NAME} 
                            PUBLIC 
                            ${PROJECT_SOURCE_DIR}
                            ${CMAKE_CURRENT_SOURCE_DIR}/gl3w
                            )

target_link_libraries(${PROJECT_NAME} 
                      ${OPENGL_gl_LIBRARY}
                    ) 
