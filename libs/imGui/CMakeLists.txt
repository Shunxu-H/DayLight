
cmake_minimum_required(VERSION 3.0)

project(imGui)

set(SOURCE  imgui_demo.cpp 
            imgui_draw.cpp
            imgui_widgets.cpp
            imgui.cpp
            )
set(HEADER  imconfig.h 
            imgui_internal.h 
            imgui.h 
            imstb_rectpack.h
            imstb_textedit.h 
            imstb_truetype.h
)

add_library(${PROJECT_NAME} ${SOURCE} ${HEADER})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})