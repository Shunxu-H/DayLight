cmake_minimum_required(VERSION 3.0)

project(DayLight)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -fPIC")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -fPIC")

set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(LIBS_DIR ${PROJECT_SOURCE_DIR}/libs)

add_subdirectory(${LIBS_DIR}/GLoader)
add_subdirectory(${LIBS_DIR}/imGui)
add_subdirectory(${SOURCE_DIR}/Common)
add_subdirectory(${SOURCE_DIR}/IO)
add_subdirectory(${SOURCE_DIR}/Lumos)
add_subdirectory(${SOURCE_DIR}/Patronus)
add_subdirectory(${SOURCE_DIR}/DayLightViewer)
