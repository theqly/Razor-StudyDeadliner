cmake_minimum_required(VERSION 3.22)
project(Razor)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(IMGUI_DIR dependencies/imgui)
set(IMGUI_SRC ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
        ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer2.cpp)

set(RAZOR_SRC src/main.cpp src/task/task.cpp src/subject/subject.cpp)

add_executable(Razor ${IMGUI_SRC} ${RAZOR_SRC})

target_include_directories(Razor PUBLIC ${SDL2_LIBRARIES})
target_include_directories(Razor PUBLIC include/)
target_include_directories(Razor PUBLIC dependencies/imgui dependencies/imgui/backends)

target_link_libraries(Razor ${SDL2_LIBRARIES} SDL2 SDL2main)
