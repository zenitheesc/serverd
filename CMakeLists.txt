 cmake_minimum_required(VERSION 3.16.3)
 project(ServerD)

 add_definitions("-std=c++17")

 include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
 conan_basic_setup()

 add_executable(serverd src/server.cpp src/utils.cpp src/message-buffer.cpp)
 target_link_libraries(serverd ${CONAN_LIBS})
