#
#   imgui-sfml: https://github.com/eliasdaler/imgui-sfml
#

include(cmake/sfml.cmake)
include(cmake/imgui.cmake)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(/MT /MTd)
else()
    add_compile_options(/MT)
endif()

set(IMGUI_SFML_BUILD_EXAMPLES ON)

find_package(ImGui-SFML CONFIG REQUIRED)

add_library(InitIMGUI_SFML INTERFACE)
add_library(lib::imgui_sfml ALIAS InitIMGUI_SFML)

target_link_libraries(InitIMGUI_SFML INTERFACE ImGui-SFML::ImGui-SFML lib::sfml lib::imgui)