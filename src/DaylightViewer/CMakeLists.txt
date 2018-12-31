
cmake_minimum_required(VERSION 3.0)

project(DaylightViewer)


# set library name for later use 
set(LibImGui imGui)

set(SOURCE  ./imgui_impl_glfw.cpp
            ./imgui_impl_opengl3.cpp
            ./main.cpp
            ./WindowManagerImgui.cpp
            )
set(HEADER  ./imgui_impl_glfw.h
            ./imgui_impl_opengl3.h
            ./WindowManagerImgui.h
)


find_package( Bullet REQUIRED )
find_package( OpenCV REQUIRED )

# external dependency
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADER})
target_link_libraries(${PROJECT_NAME} 
                        ${LibImGui} 
                        ${OPENGL_gl_LIBRARY}
                        ${OpenCV_LIBS}
                        GLoader
                        IO
                        Common
                        Patronus
                        Lumos
                        glfw
                        stdc++fs
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


include_directories(${GLoader_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/src)

target_link_libraries( ${PROJECT_NAME} ${BULLET_LIBRARIES} )
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC /usr/local/include/bullet/ )


# Copy resource files 
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>)