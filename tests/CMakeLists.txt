project(tests VERSION 1.0)

find_package(GTest CONFIG REQUIRED)

add_executable(tests tests.cpp)
if (MSVC)
      set_property(TARGET tests PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else()
endif()

target_include_directories(tests PUBLIC PUBLIC "../include")
target_link_libraries(tests PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)

add_test(NAME tests COMMAND tests)