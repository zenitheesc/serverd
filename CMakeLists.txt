 cmake_minimum_required(VERSION 3.18.4)
 project(ServerD)

 add_definitions("-std=c++11")

 include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
 conan_basic_setup()

 add_executable(serverd src/server.cpp src/utils.cpp)
 target_link_libraries(serverd ${CONAN_LIBS})
