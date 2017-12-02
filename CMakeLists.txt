
cmake_minimum_required(VERSION 2.8)
project( DayLight )


include(glbinding-config.cmake)

# The version number.
set ( DayLight_VERSION_MAJOR 1)
set ( DayLight_VERSION_MINOR 0)

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


SET(GCC_COVERAGE_COMPILE_FLAGS "-lGLESv2")


# set warnig option
if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Werror")
endif ( CMAKE_COMPILER_IS_GNUCC )
if ( MSVC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
endif ( MSVC )



# Check for standard to use
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(EGL_LIBRARIES ${EGL_LIBRARY} )
set(CMAKE_BUILD_TYPE Debug)


find_path(EGL_INCLUDE_DIR NAMES EGL/egl.h)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )
set( EGL_NAMES ${EGL_NAMES} egl EGL)
find_library(EGL_LIBRARY NAMES ${EGL_NAMES})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(EGL DEFAULT_MSG EGL_LIBRARY EGL_INCLUDE_DIR)

mark_as_advanced(EGL_INCLUDE_DIR EGL_LIBRARY)

find_package( OpenCV REQUIRED )
find_package( OpenGL REQUIRED )
find_package( X11 REQUIRED )
# find_package( glfw3 REQUIRED)
find_package( GLEW REQUIRED )
find_package( GLUT REQUIRED )
find_package( Bullet REQUIRED )
find_package( glbinding REQUIRED )

# find_package( BGM REQUIRED)


file(GLOB_RECURSE DayLight_SOURCES "src/*.cpp")
file(GLOB_RECURSE DayLight_HEADERS "includes/*.h")


set (DayLight_INCLUDE_DIRS "")
foreach (_headerFile ${DayLight_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND DayLight_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES DayLight_INCLUDE_DIRS)

add_executable (DayLight ${DayLight_SOURCES})
target_include_directories(DayLight PRIVATE ${DayLight_INCLUDE_DIRS})
target_include_directories(DayLight PRIVATE ./Includes)
target_include_directories(DayLight PUBLIC /usr/local/include/bullet/ )

# target_link_libraries(DayLight
#     ${CMAKE_CURRENT_SOURCE_DIR}/bullet/BulletDynamics/libBulletDynamics.a
#     ${CMAKE_CURRENT_SOURCE_DIR}/bullet/BulletCollision/libBulletCollision.a
#     ${CMAKE_CURRENT_SOURCE_DIR}/bullet/LinearMath/libLinearMath.a
#     -lGL -lGLU)

target_link_libraries( DayLight stdc++fs)
target_link_libraries( DayLight ${BULLET_LIBRARIES} )

target_link_libraries( DayLight ${OpenCV_LIBS} )
target_link_libraries( DayLight ${OPENGL_LIBRARIES} )
target_link_libraries( DayLight ${X11_LIBRARIES})
target_link_libraries( DayLight ${EGL_LIBRARIES} ) #here you can put your opengl linking library.
# target_link_libraries( DayLight ${GLFW3_LIBRARY})
target_link_libraries( DayLight ${GLEW_LIBRARY})
target_link_libraries( DayLight ${GLUT_LIBRARIES})
target_link_libraries( DayLight ${GLBINDING_LIBRARIES})


message(STATUS "GLBINDING_LIBRARIES = ${GLBINDING_LIBRARIES}")
message(STATUS "GLBINDING_INCLUDES = ${GLBINDING_INCLUDES}")