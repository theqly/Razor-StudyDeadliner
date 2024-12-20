#ifndef UI_CONTROLLER_H
#define UI_CONTROLLER_H
#include <subjects_controller.h>
#include <SDL.h>

class ui_controller {
private:
  subjects_controller _subjects_controller;
  bool _is_running;

public:
  explicit ui_controller(const subjects_controller & subjects_controller);
  void handle_input();

  bool is_running() const;
};

#endif // UI_CONTROLLER_H
