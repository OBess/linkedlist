#
#   SFML: https://github.com/SFML/SFML
#

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

add_library(InitSFML INTERFACE)
add_library(lib::sfml ALIAS InitSFML)

target_link_libraries(InitSFML INTERFACE sfml-system sfml-network sfml-graphics sfml-window)