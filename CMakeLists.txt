cmake_minimum_required(VERSION 3.22)
project(Razor)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

include(FetchContent)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(json)

set(IMGUI_DIR dependencies/imgui)
set(IMGUI_SRC ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
        ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer2.cpp)

set(RAZOR_SRC src/main.cpp src/task.cpp src/subject.cpp src/file_manager.cpp src/ui/ui.cpp src/ui/ui_controller.cpp src/subjects_controller.cpp)

add_executable(Razor ${IMGUI_SRC} ${RAZOR_SRC})

target_include_directories(Razor PUBLIC ${SDL2_INCLUDE_DIRS})
target_include_directories(Razor PUBLIC include/)
target_include_directories(Razor PUBLIC dependencies/imgui dependencies/imgui/backends)

target_link_libraries(Razor ${SDL2_LIBRARIES} SDL2 SDL2main nlohmann_json::nlohmann_json)
