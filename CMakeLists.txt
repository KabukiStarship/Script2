cmake_minimum_required (VERSION 3.10)
project (Crabs)

target_include_directories(Tutorial PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )
                           
add_executable(Crabs _Seams/_main.cpp)
