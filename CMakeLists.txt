cmake_minimum_required (VERSION 3.10)
project (Script2)

target_include_directories(Tutorial PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )
                           
add_executable(Script2 _Seams/_main.cpp)
