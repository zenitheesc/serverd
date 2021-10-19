add_executable(utils-test utils-test.cpp  ../src/utils.cpp)

target_link_libraries(utils-test ${CONAN_LIBS})

include(GoogleTest)
gtest_discover_tests(utils-test)
