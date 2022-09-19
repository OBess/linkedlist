cmake_minimum_required(VERSION 3.15)
project(linkedlist VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# - Директорія для згенерованих файлів
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/deploy)

enable_testing()
add_subdirectory(tests)

file(GLOB src *.cpp *.hpp *.c *.h *.cc)
add_executable(linkedlist ${src})

target_include_directories(linkedlist PUBLIC "include")