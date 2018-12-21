
cmake_minimum_required(VERSION 3.0)

project(IO)

set(SOURCE  ./View.cpp
            ./WindowManagerX11.cpp
            ./PerspectiveView.cpp
            ./btDebugDrawer.cpp
            ./WindowManager.cpp
            ./Widget.cpp
            ./EventCatcher.cpp
            ./View_renderer.cpp
            ./View_bullet.cpp
            ./Event/CursorEvent.cpp
            )

set(HEADER  ./Widget.h
            ./btDebugDrawer.h
            ./View_renderer.h
            ./View.h
            ./PerspectiveView.h
            ./WindowManagerX11.h
            ./WindowManager.h
            ./View_bullet.h
            ./EventCatcher.h
            ./Event/CursorEvent.h
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