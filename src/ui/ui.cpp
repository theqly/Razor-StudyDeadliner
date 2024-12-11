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
  static int selected_subject_id = -1;
  static bool edit_subject_modal_open = false;

  ImGui::Begin("Manage Subjects");

  ImGui::Text("Add a new subject:");
  ImGui::InputText("##SubjectName", subject_name, sizeof(subject_name));
  ImGui::SameLine();
  if (ImGui::Button("Add")) {
    if (strlen(subject_name) > 0) {
      _subjects_controller.add_subject(subject_name);
      _subjects_controller.handle_update();
      subject_name[0] = '\0';
    }
  }

  ImGui::Separator();

  ImGui::Text("Subjects:");
  for (auto &subj : _subjects_controller.get_subjects()) {
    ImGui::Text("ID: %d, Name: %s, Description: %s, Readiness: %.2f%%", subj.get_id(),
                subj.get_name().c_str(), subj.get_description().c_str(), subj.get_readiness() * 100.0f);

    if (ImGui::Button(("Open##" + std::to_string(subj.get_id())).c_str())) {
      _cur_state = SUBJECT;
      _cur_subject = subj.get_id();
    }
    ImGui::SameLine();
    if (ImGui::Button(("Edit##" + std::to_string(subj.get_id())).c_str())) {
      selected_subject_id = subj.get_id();
      edit_subject_modal_open = true;
    }
    ImGui::SameLine();
    if (ImGui::Button(("Delete##" + std::to_string(subj.get_id())).c_str())) {
      _subjects_controller.remove_subject(subj.get_id());
      _subjects_controller.handle_update();
    }
  }

  ImGui::Separator();

  if (ImGui::Button("Exit")) {
    exit(0);
  }

  ImGui::End();

  if (edit_subject_modal_open) {
    subject &subject = _subjects_controller.get_subject_by_id(selected_subject_id);
    static char edit_subject_name[128] = "";
    static char edit_subject_description[128] = "";
    strncpy(edit_subject_name, subject.get_name().c_str(), sizeof(edit_subject_name));
    strncpy(edit_subject_description, subject.get_description().c_str(), sizeof(edit_subject_description));

    ImGui::OpenPopup("Edit Subject");
    if (ImGui::BeginPopupModal("Edit Subject", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
      ImGui::InputText("New Name", edit_subject_name, sizeof(edit_subject_name));
      ImGui::InputText("New Description", edit_subject_description, sizeof(edit_subject_description));
      if (ImGui::Button("Save")) {
        subject.change_name(edit_subject_name);
        subject.change_description(edit_subject_description);
        _subjects_controller.handle_update();
        edit_subject_name[0] = '\0';
        edit_subject_description[0] = '\0';
        edit_subject_modal_open = false;
        ImGui::CloseCurrentPopup();
      }
      ImGui::SameLine();
      if (ImGui::Button("Cancel")) {
        edit_subject_modal_open = false;
        ImGui::CloseCurrentPopup();
      }
      ImGui::EndPopup();
    }
  }
}

void ui::draw_subject_menu(const int subject_id) {
  static char task_name[128] = "";
  static char task_description[256] = "";
  static char task_deadline[64] = "";
  static int selected_task_id = -1;
  static bool edit_task_modal_open = false;

  ImGui::Begin("Manage Tasks");

  auto &subject = _subjects_controller.get_subject_by_id(subject_id);

  ImGui::Text("Subject: %s", subject.get_name().c_str());
  ImGui::Text("Readiness: %.2f%%", subject.get_readiness() * 100.0f);

  ImGui::Separator();

  ImGui::Text("Add a new task:");
  ImGui::InputText("Task name", task_name, sizeof(task_name));
  ImGui::InputText("Description", task_description, sizeof(task_description));
  ImGui::InputText("Deadline", task_deadline, sizeof(task_deadline));

  if (ImGui::Button("Add task")) {
    if (strlen(task_name) > 0 && strlen(task_deadline) > 0) {
      subject.add_task(task_name, task_description, task_deadline);
      _subjects_controller.handle_update();
      task_name[0] = '\0';
      task_description[0] = '\0';
      task_deadline[0] = '\0';
    }
  }

  ImGui::Separator();

  ImGui::Text("Tasks:");
  for (auto &task : subject.get_tasks()) {
    ImGui::Text("Task ID: %d, Name: %s, Deadline: %s, Progress: %.2f%%",
                task.get_id(), task.get_name().c_str(), task.get_deadline().c_str(),
                task.get_readiness() * 100.0f);

    if (ImGui::Button(("Edit##" + std::to_string(task.get_id())).c_str())) {
      selected_task_id = task.get_id();
      edit_task_modal_open = true;
    }
    ImGui::SameLine();
    if (ImGui::Button(("Delete##" + std::to_string(task.get_id())).c_str())) {
      subject.remove_task(task.get_id());
      _subjects_controller.handle_update();
    }
  }

  ImGui::Separator();

  if (ImGui::Button("Back")) {
    _cur_state = MAIN;
  }

  ImGui::End();

  if (edit_task_modal_open) {
    auto &task = subject.get_task_by_id(selected_task_id);
    static char edit_task_name[128];
    static char edit_task_description[256];
    static char edit_task_deadline[64];
    static int edit_task_progress;

    strncpy(edit_task_name, task.get_name().c_str(), sizeof(edit_task_name));
    strncpy(edit_task_description, task.get_description().c_str(), sizeof(edit_task_description));
    strncpy(edit_task_deadline, task.get_deadline().c_str(), sizeof(edit_task_deadline));
    edit_task_progress = static_cast<int>(task.get_readiness() * 100);

    ImGui::OpenPopup("Edit Task");
    if (ImGui::BeginPopupModal("Edit Task", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
      ImGui::InputText("Name", edit_task_name, sizeof(edit_task_name));
      ImGui::InputText("Description", edit_task_description, sizeof(edit_task_description));
      ImGui::InputText("Deadline", edit_task_deadline, sizeof(edit_task_deadline));
      ImGui::SliderInt("Progress", &edit_task_progress, 0, 100);

      if (ImGui::Button("Save")) {
        task.change_name(edit_task_name);
        task.change_description(edit_task_description);
        task.change_deadline(edit_task_deadline);
        task.change_readiness(edit_task_progress / 100.0f);
        _subjects_controller.handle_update();
        edit_task_name[0] = '\0';
        edit_task_description[0] = '\0';
        edit_task_deadline[0] = '\0';
        edit_task_progress = 0;
        edit_task_modal_open = false;
        ImGui::CloseCurrentPopup();
      }
      ImGui::SameLine();
      if (ImGui::Button("Cancel")) {
        edit_task_modal_open = false;
        ImGui::CloseCurrentPopup();
      }
      ImGui::EndPopup();
    }
  }
}
