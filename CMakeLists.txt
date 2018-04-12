cmake_minimum_required(VERSION 3.0)
set(PROJECT_NAME "lua_extension")
project(${PROJECT_NAME})

# Add src code.
aux_source_directory(${CMAKE_SOURCE_DIR} SRC)

# Include headers in below directory.
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/lua-5.3.4/src/)

# 依赖库路径
link_directories(${CMAKE_SOURCE_DIR}/lua-5.3.4/src/)

# lib lua depand on lib dl, so lua should be put ahead dl.
list(APPEND LIBS lua)
list(APPEND LIBS dl)

# Use c++11.
set(CMAKE_CXX_FLAGS "-g -fPIC -std=c++11 -ldl -pipe -Wno-deprecated-declarations")

# Build program.
add_executable(test_lua ${SRC})
target_link_libraries(test_lua ${LIBS})
