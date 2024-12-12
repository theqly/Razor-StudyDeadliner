#ifndef UI_H
#define UI_H
#include <imgui.h>
#include <subjects_controller.h>

class ui {
public:
  enum menu_state {
    SUBJECTS_MENU,
    TASKS_MENU,
  };

private:
  ImGuiIO& io = ImGui::GetIO();

  ImFont* smallFont;
  ImFont* mediumFont;
  ImFont* largeFont;

  subjects_controller& _subjects_controller;
  menu_state _cur_state;

  int _cur_subject = 0;
  int _cur_task = 0;

  bool need_to_draw_add_subject_popup = false;
  bool need_to_draw_edit_subject_popup = false;

  bool need_to_draw_add_task_popup = false;
  bool need_to_draw_edit_task_popup = false;

  bool need_to_draw_delete_subject_confirmation = false;
  bool need_to_draw_delete_task_confirmation = false;

public:

  explicit ui(subjects_controller& subjects_controller);
  ~ui();

  void draw();

private:
  void draw_subjects_menu();
  void draw_tasks_menu();

  void draw_readiness_circle(const std::string &label, float readiness);

  void draw_add_subject_popup();
  void draw_edit_subject_popup(subject& s);

  void draw_add_task_popup();
  void draw_edit_task_popup(task& t);

  void draw_delete_subject_confirmation_popup();
  void draw_delete_task_confirmation_popup();
};


#endif //UI_H
