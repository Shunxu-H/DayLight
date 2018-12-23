
cmake_minimum_required(VERSION 3.0)

project(IO)

set(SOURCE  ./btDebugDrawer.cpp
            ./EventCatcher.cpp
            ./Event/CursorEvent.cpp
            ./Event/KeyboardEvent.cpp
            ./PerspectiveView.cpp
            ./View_bullet.cpp
            ./View.cpp
            ./View_renderer.cpp
            ./Widget.cpp
            ./WindowManager.cpp
            ./WindowManagerX11.cpp
            )

set(HEADER  ./btDebugDrawer.h
            ./EventCatcher.h
            ./Event/CursorEvent.h
            ./Event/KeyboardEvent.h
            ./PerspectiveView.h
            ./View_bullet.h
            ./View.h
            ./View_renderer.h
            ./Widget.h
            ./WindowManager.h
            ./WindowManagerX11.h
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