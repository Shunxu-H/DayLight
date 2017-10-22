cmake_minimum_required(VERSION 2.8)
project( DayLight )

find_package( OpenCV REQUIRED )
find_package( OpenGL REQUIRED )
find_package( X11 REQUIRED)

add_executable( DayLight main.cpp )
target_link_libraries( DayLight ${OpenCV_LIBS} )
target_link_libraries( DayLight ${OPENGL_LIBRARIES} )
target_link_libraries( DayLight ${X11_LIBRARIES})