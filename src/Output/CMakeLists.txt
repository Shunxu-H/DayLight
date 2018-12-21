
cmake_minimum_required(VERSION 3.0)

project(Output)

set(SOURCE  ./View.cpp
            ./WindowManager.cpp
            ./PerspectiveView.cpp
            ./btDebugDrawer.cpp
            ./WindowManager_base.cpp
            ./Widget.cpp
            ./EventCatcher.cpp
            ./View_renderer.cpp
            ./View_bullet.cpp
            ./Input/CursorEvent.cpp
            )

set(HEADER  ./Widget.h
            ./btDebugDrawer.h
            ./View_renderer.h
            ./View.h
            ./PerspectiveView.h
            ./WindowManager.h
            ./WindowManager_base.h
            ./View_bullet.h
            ./EventCatcher.h
            ./Input/CursorEvent.h
)


# external dependency
# find_package(OpenGL REQUIRED)

add_library(${PROJECT_NAME} ${SOURCE} ${HEADER})
target_link_libraries(${PROJECT_NAME} 
#                         ${OPENGL_gl_LIBRARY}
                    ) 


include_directories(${GLoader_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/src)

target_link_libraries( ${PROJECT_NAME} ${BULLET_LIBRARIES} )
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC /usr/local/include/bullet/ )
# if (APPLE)
#     target_link_libraries(${PROJECT_NAME} 
#         "-framework Cocoa"
#         "-framework IOKit" 
#         "-framework CoreVideo"
#     ) 
# endif()