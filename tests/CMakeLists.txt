cmake_minimum_required (VERSION 2.6)
project (Script2)
set (Script2_VERSION_MAJOR 0)
set (Script2_VERSION_MINOR 9)

configure_file (
  "${PROJECT_SOURCE_DIR}/global.h"
  "${PROJECT_BINARY_DIR}/pch.h"
  )

include_directories("${PROJECT_BINARY_DIR}")

add_executable(Script2Tests
    script2_pch.cc)
