cmake_minimum_required (VERSION 3.10)
project (script2)

target_include_directories(Tutorial PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )
                           
add_executable(script2 _seams/_main.cpp)
