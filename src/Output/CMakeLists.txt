
cmake_minimum_required(VERSION 3.0)

project(Output)

set(SOURCE  ./View.cpp
            ./WindowManager.cpp
            ./PerspectiveView.cpp
            ./btDebugDrawer.cpp
            ./WindowManager_base.cpp
            ./Widget.cpp
            ./WindowManager_headless.cpp
            ./PhysicalWorld.cpp
            ./EventCatcher.cpp
            ./View_renderer.cpp
            ./View_bullet.cpp
            )

set(HEADER  ./Widget.h
            ./btDebugDrawer.h
            ./View_renderer.h
            ./View.h
            ./WindowManager_headless.h
            ./PerspectiveView.h
            ./WindowManager.h
            ./WindowManager_base.h
            ./View_bullet.h
            ./EventCatcher.h
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