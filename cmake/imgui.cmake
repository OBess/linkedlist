#
#   imgui: https://github.com/ocornut/imgui
#

find_package(imgui CONFIG REQUIRED)

add_library(InitiImgui INTERFACE)
add_library(lib::imgui ALIAS InitiImgui)

target_link_libraries(InitiImgui INTERFACE imgui::imgui)