
cmake_minimum_required(VERSION 2.8)
project( DayLight )

include_directories(includes)

add_subdirectory(src)

find_path(EGL_INCLUDE_DIR
  NAMES
    EGL/egl.h
  PATHS
    ${EGL_ROOT_DIR}/include
    /usr/local/include
    /usr/include)

find_library(EGL_LIBRARY
  NAMES
    EGL
  PATHS
    ${EGL_ROOT_DIR}/lib
    /usr/local/lib
    /usr/lib)



set(EGL_LIBRARIES ${EGL_LIBRARY} )
set(CMAKE_BUILD_TYPE Debug)


SET(GCC_COVERAGE_COMPILE_FLAGS "-lGLESv2")


find_path(EGL_INCLUDE_DIR NAMES EGL/egl.h)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
set(EGL_NAMES ${EGL_NAMES} egl EGL)
find_library(EGL_LIBRARY NAMES ${EGL_NAMES})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(EGL DEFAULT_MSG EGL_LIBRARY EGL_INCLUDE_DIR)

mark_as_advanced(EGL_INCLUDE_DIR EGL_LIBRARY)

find_package( OpenCV REQUIRED )
find_package( OpenGL REQUIRED )
find_package( X11 REQUIRED)
# find_package( glfw3 REQUIRED)
find_package( GLEW REQUIRED)
find_package( GLUT REQUIRED)

# find_package( BGM REQUIRED)


add_executable( DayLight main.cpp )
target_link_libraries( DayLight ${OpenCV_LIBS} )
target_link_libraries( DayLight ${OPENGL_LIBRARIES} )
target_link_libraries( DayLight ${X11_LIBRARIES})
target_link_libraries( DayLight ${EGL_LIBRARIES} ) #here you can put your opengl linking library.
# target_link_libraries( DayLight ${GLFW3_LIBRARY})
target_link_libraries( DayLight ${GLEW_LIBRARY})
target_link_libraries( DayLight ${GLUT_LIBRARIES})
