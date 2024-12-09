#include "ui/ui_controller.h"

#include <imgui_impl_sdl2.h>

ui_controller::ui_controller(const subjects_controller &subjects_controller)
    : _subjects_controller(subjects_controller), running(1) {}

void ui_controller::handle_input() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    ImGui_ImplSDL2_ProcessEvent(&event);
    if (event.type == SDL_QUIT) {
      running = false;
      return;
    }
    if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
        running = false;
        break;
      case SDLK_n:
        _subjects_controller.add_subject("New Subject");
        break;
      default:
        break;
      }
    }
  }
}

bool ui_controller::is_running() const { return running; }
