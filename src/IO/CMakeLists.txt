
cmake_minimum_required(VERSION 3.0)

project(IO)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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


find_package( OpenCV REQUIRED )
find_package( X11 REQUIRED )
add_library(${PROJECT_NAME} ${SOURCE} ${HEADER})
target_link_libraries(  ${PROJECT_NAME} 
                        ${OpenCV_LIBS}
                    ) 

include_directories(${GLoader_SOURCE_DIR} ${OpenCV_INCLUDE_DIRS} ${X11_LIBRARIES} ${CMAKE_SOURCE_DIR}/src)

target_link_libraries( ${PROJECT_NAME} ${BULLET_LIBRARIES} )
target_include_directories(${PROJECT_NAME} PUBLIC 
                            ${PROJECT_SOURCE_DIR}
                            ${X11_INCLUDE_DIR} 
                            /usr/local/include/bullet/ )

target_link_libraries(${PROJECT_NAME} "-lstdc++fs")
# if (APPLE)
#     target_link_libraries(${PROJECT_NAME} 
#         "-framework Cocoa"
#         "-framework IOKit" 
#         "-framework CoreVideo"
#     ) 
# endif()