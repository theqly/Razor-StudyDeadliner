#include "ui/ui.h"
#include <imgui.h>

ui::ui(subjects_controller &subjects_controller)
    : _subjects_controller(subjects_controller), _cur_state(MAIN) {}
ui::~ui() {}

void ui::draw() {
  switch (_cur_state) {
  case MAIN: {
    draw_main_menu();
    break;
  }

  case SUBJECT: {
    draw_subject_menu(_cur_subject);
    break;
  }

  }
}

void ui::draw_main_menu() {
  static char subject_name[128] = "";

  ImGui::Begin("Manage Subjects");

  ImGui::InputText("Subject name", subject_name, sizeof(subject_name));

  if (ImGui::Button("Add subject")) {
    if (strlen(subject_name) > 0) {
      _subjects_controller.add_subject(subject_name);
      subject_name[0] = '\0';
    }
  }

  ImGui::Separator();

  for (auto &subj : _subjects_controller.get_subjects()) {
    ImGui::Text("ID: %d, Name: %s, Readiness: %.2f%%", subj.get_id(),
                subj.get_name().c_str(), subj.get_readiness() * 100.0f);
    if (ImGui::Button(("Open##" + std::to_string(subj.get_id())).c_str())) {
      _cur_state = SUBJECT;
      _cur_subject = subj.get_id();
    }
    ImGui::SameLine();
    if (ImGui::Button(("Delete##" + std::to_string(subj.get_id())).c_str())) {
      _subjects_controller.remove_subject(subj.get_id());
    }
  }

  ImGui::Separator();

  if (ImGui::Button("Exit")) {
    exit(0);
  }

  ImGui::End();
}

void ui::draw_subject_menu(const int subject_id) {
  static char task_name[128] = "";

  ImGui::Begin("Manage Tasks");

  ImGui::InputText("Task name", task_name, sizeof(task_name));

  if (ImGui::Button("Add task")) {
    if (strlen(task_name) > 0) {
      auto &subject = _subjects_controller.get_subject_by_id(subject_id);
      task new_task(subject.get_tasks().size() + 1, task_name, "New task description");
      subject.add_task(new_task);
      task_name[0] = '\0';
    }
  }

  ImGui::Separator();

  const auto &subject = _subjects_controller.get_subject_by_id(subject_id);
  ImGui::Text("Subject: %s", subject.get_name().c_str());
  ImGui::Text("Readiness: %.2f%%", subject.get_readiness() * 100.0f);

  for (auto &task : subject.get_tasks()) {
    ImGui::Text("Task ID: %d, Name: %s, Deadline: %s, Readiness: %.2f%%",
                task.get_id(), task.get_name().c_str(), task.get_deadline().c_str(),
                task.get_readiness() * 100.0f);
    if (ImGui::Button(
            ("Mark as Complete##" + std::to_string(task.get_id())).c_str())) {
      task.change_readiness(1.0f);
    }
  }

  if (ImGui::Button("Back")) {
    _cur_state = MAIN;
  }

  ImGui::End();
}
