#include "ui/ui_controller.h"

#include <imgui_impl_sdl2.h>

ui_controller::ui_controller(const subjects_controller &subjects_controller)
    : _subjects_controller(subjects_controller), _is_running(true) {}

void ui_controller::handle_input() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    ImGui_ImplSDL2_ProcessEvent(&event);

    if (event.type == SDL_QUIT) {
      _is_running = false;
      return;
    }

    if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
        _is_running = false;
        break;
      default:
        break;
      }
    }
  }
}

bool ui_controller::is_running() const { return _is_running; }
