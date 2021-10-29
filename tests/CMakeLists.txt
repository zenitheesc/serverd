add_executable(message-test message-test.cpp  ../src/message-buffer.cpp)
target_link_libraries(message-test ${CONAN_LIBS})

include(GoogleTest)
gtest_discover_tests(message-test)
