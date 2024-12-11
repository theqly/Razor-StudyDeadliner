#ifndef UI_H
#define UI_H
#include <SDL.h>
#include <subjects_controller.h>

class ui {
public:
  enum menu_state {
    MAIN,
    SUBJECT,
  };

private:
  subjects_controller& _subjects_controller;
  menu_state _cur_state;

  int _cur_subject = 0;
  int _cur_task = 0;

public:

  explicit ui(subjects_controller& subjects_controller);
  ~ui();

  void draw();

private:
  void draw_main_menu();
  void draw_subject_menu(int subject_id);
};


#endif //UI_H
