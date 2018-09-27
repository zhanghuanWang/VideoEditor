
cmake_minimum_required(VERSION 3.4.1)

set(dir_cpp src/main/cpp)
set(dir_gles src/main/cpp/gles)

add_library( gles
             SHARED
             ${dir_gles}/gles.cpp
             ${dir_gles}/glutil.cpp
             ${dir_gles}/EGLCore.cpp
             ${dir_gles}/Beauty.cpp )

include_directories( ${dir_cpp}/common )

target_link_libraries( gles

                       EGL
                       GLESv3
                       android
                       log )