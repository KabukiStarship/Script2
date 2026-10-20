cmake_minimum_required (VERSION 3.10)
project (ASCIICrabs)

set (CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ASCIICrabs _Seams/_Main.cpp)

target_include_directories(ASCIICrabs PRIVATE
  "${PROJECT_BINARY_DIR}"
  "${PROJECT_SOURCE_DIR}"
  "${PROJECT_SOURCE_DIR}/_Seams"
)

# Focused native Room/List regression; exit code is the seam test signal.
add_executable(RoomBindingTests _Seams/RoomBinding.cpp)
target_include_directories(RoomBindingTests PRIVATE
  "${PROJECT_SOURCE_DIR}/_Seams"
  "${PROJECT_SOURCE_DIR}"
)

