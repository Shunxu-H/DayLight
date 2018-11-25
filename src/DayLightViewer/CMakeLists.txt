
cmake_minimum_required(VERSION 3.0)

project(DayLightViewer)


# set library name for later use 
set(LibImGui imGui)

set(SOURCE  imgui_impl_glfw.cpp 
            imgui_impl_opengl3.cpp
            libs/gl3w/GL/gl3w.c
            Window.cpp
            main.cpp
            )
set(HEADER  imgui_impl_glfw.h 
            imgui_impl_opengl3.h 
            Window.h
)

include_directories(libs/gl3w)

# external dependency
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADER})
target_link_libraries(${PROJECT_NAME} 
                        ${LibImGui} 
                        ${OPENGL_gl_LIBRARY}
                        glfw
                    ) 
if (APPLE)
    target_link_libraries(${PROJECT_NAME} 
        "-framework Cocoa"
        "-framework IOKit" 
        "-framework CoreVideo"
    ) 
endif()
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})