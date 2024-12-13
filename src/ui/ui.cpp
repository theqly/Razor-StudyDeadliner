#include "ui/ui.h"
#include <imgui.h>
#include <imgui_internal.h>
#include <iostream>

#define MAX_SUBJECT_NAME_LEN 128
#define MAX_SUBJECT_DESCRIPTION_LEN 256
#define MAX_TASK_NAME_LEN 128
#define MAX_TASK_DESCRIPTION_LEN 256

ui::ui(subjects_controller &subjects_controller)
    : _subjects_controller(subjects_controller), _cur_state(SUBJECTS_MENU) {
  smallFont = io.Fonts->AddFontFromFileTTF((std::string(RESOURCES_PATH) + "/fonts/Roboto-Regular.ttf").c_str(), 18.0f, nullptr, io.Fonts->GetGlyphRangesCyrillic());
  mediumFont = io.Fonts->AddFontFromFileTTF((std::string(RESOURCES_PATH) + "/fonts/Roboto-Regular.ttf").c_str(), 22.0f, nullptr, io.Fonts->GetGlyphRangesCyrillic());
  largeFont = io.Fonts->AddFontFromFileTTF((std::string(RESOURCES_PATH) + "/fonts/Roboto-Regular.ttf").c_str(), 26.0f, nullptr, io.Fonts->GetGlyphRangesCyrillic());

  io.FontDefault = smallFont;
}

ui::~ui() = default;

void ui::draw() {
  switch (_cur_state) {
  case SUBJECTS_MENU: {
    draw_subjects_menu();
    break;
  }

  case TASKS_MENU: {
    draw_tasks_menu();
    break;
  }
  }
}

void ui::draw_subjects_menu() {
  ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize, ImGuiCond_Once);
  ImGui::Begin("Subjects Menu");

  if (ImGui::Button("Add Subject")) {
    need_to_draw_add_subject_popup = true;
  }

  ImGui::Separator();

  for (auto &subj : _subjects_controller.get_subjects()) {
    ImGui::BeginGroup();

    ImGui::PushFont(mediumFont);
    ImGui::Text("%s", subj.get_name().c_str());
    ImGui::PopFont();

    ImGui::TextWrapped("Description: %s", subj.get_description().c_str());

    ImGui::TextWrapped("Readiness: %.2f%%", subj.get_readiness() * 100.0f);

    if (ImGui::Button(("Open##" + std::to_string(subj.get_id())).c_str())) {
      _cur_state = TASKS_MENU;
      _cur_subject = subj.get_id();
      ImGui::EndGroup();
      ImGui::End();
      return;
    }
    ImGui::SameLine();
    if (ImGui::Button(("Edit##" + std::to_string(subj.get_id())).c_str())) {
      need_to_draw_edit_subject_popup = true;
      _cur_subject = subj.get_id();
    }
    ImGui::SameLine();
    if (ImGui::Button(("Delete##" + std::to_string(subj.get_id())).c_str())) {
      _cur_subject = subj.get_id();
      need_to_draw_delete_subject_confirmation = true;
    }

    ImGui::Separator();
    ImGui::EndGroup();
  }

  ImGui::Separator();

  float total_readiness = _subjects_controller.get_total_readiness();
  draw_readiness_circle("Overall Readiness", total_readiness);

  ImGui::Separator();

  if (ImGui::Button("Exit")) {
    exit(0);
  }

  if(need_to_draw_add_subject_popup) draw_add_subject_popup();
  if(need_to_draw_edit_subject_popup) draw_edit_subject_popup(_subjects_controller.get_subject_by_id(_cur_subject));
  if (need_to_draw_delete_subject_confirmation) draw_delete_subject_confirmation_popup();

  ImGui::End();
}

void ui::draw_tasks_menu() {
  ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize, ImGuiCond_Once);
  ImGui::Begin("Tasks Menu");

  auto &subject = _subjects_controller.get_subject_by_id(_cur_subject);

  ImGui::PushFont(largeFont);
  ImGui::Text("%s", subject.get_name().c_str());
  ImGui::PopFont();

  if (ImGui::Button("Add Task")) {
    need_to_draw_add_task_popup = true;
  }

  ImGui::Separator();

  ImGui::PushFont(mediumFont);
  ImGui::Text("Tasks:");
  ImGui::PopFont();

  ImGui::Separator();

  for (auto &task : subject.get_tasks()) {
    ImGui::BeginGroup();

    ImGui::PushFont(mediumFont);
    ImGui::Text("%s", task.get_name().c_str());
    ImGui::PopFont();

    ImGui::TextWrapped("Description: %s", task.get_description().c_str());

    ImGui::TextWrapped("Deadline: %s", task.get_deadline().c_str());

    ImGui::TextWrapped("Readiness: %.2f%%", task.get_readiness() * 100.0f);

    if (ImGui::Button(("Mark as done##" + std::to_string(task.get_id())).c_str())) {
      task.change_readiness(1.0f);
      _subjects_controller.handle_update();
    }
    ImGui::SameLine();
    if (ImGui::Button(("Edit##" + std::to_string(task.get_id())).c_str())) {
      need_to_draw_edit_task_popup = true;
      _cur_task = task.get_id();
    }
    ImGui::SameLine();
    if (ImGui::Button(("Delete##" + std::to_string(task.get_id())).c_str())) {
      _cur_task = task.get_id();
      need_to_draw_delete_task_confirmation = true;
    }

    ImGui::EndGroup();
  }

  ImGui::Separator();

  float readiness = subject.get_readiness();
  draw_readiness_circle("Readiness", readiness);

  ImGui::Separator();

  if (ImGui::Button("Back")) {
    _cur_state = SUBJECTS_MENU;
  }

  if(need_to_draw_add_task_popup) draw_add_task_popup();
  if(need_to_draw_edit_task_popup) draw_edit_task_popup(_subjects_controller.get_subject_by_id(_cur_subject).get_task_by_id(_cur_task));
  if (need_to_draw_delete_task_confirmation) draw_delete_task_confirmation_popup();

  ImGui::End();
}

void ui::draw_readiness_circle(const std::string &label, const float readiness) {
  const float radius = 50.0f;
  const float thickness = 5.0f;
  const ImVec2 pos = ImGui::GetCursorScreenPos();
  const ImVec2 center = ImVec2(pos.x + radius, pos.y + radius);

  ImDrawList *draw_list = ImGui::GetWindowDrawList();

  draw_list->AddCircle(center, radius, IM_COL32(200, 200, 200, 255), 100, thickness);

  const float start_angle = -IM_PI / 2.0f;
  const float end_angle_ready = start_angle + (2.0f * IM_PI * readiness);
  const float end_angle_not_ready = start_angle + (2.0f * IM_PI);

  draw_list->PathArcTo(center, radius, start_angle, end_angle_ready, 100);
  draw_list->PathStroke(IM_COL32(100, 200, 100, 255), false, thickness);

  draw_list->PathArcTo(center, radius, end_angle_ready, end_angle_not_ready, 100);
  draw_list->PathStroke(IM_COL32(200, 100, 100, 255), false, thickness);

  ImGui::Dummy(ImVec2(radius * 2, radius * 2));
  ImGui::SetCursorScreenPos(ImVec2(pos.x, pos.y + radius * 2 + 10));
  ImGui::Text("%s: %.2f%%", label.c_str(), readiness * 100.0f);
}

void ui::draw_add_subject_popup() {
  ImGui::OpenPopup("Add Subject");
  static char s_name[MAX_SUBJECT_NAME_LEN];
  static char s_description[MAX_SUBJECT_DESCRIPTION_LEN];

  if (!ImGui::BeginPopupModal("Add Subject", nullptr,
                              ImGuiWindowFlags_AlwaysAutoResize)) return;

  ImGui::InputText("Name", s_name, MAX_SUBJECT_NAME_LEN);
  ImGui::InputText("Description", s_description, MAX_SUBJECT_DESCRIPTION_LEN);

  if (ImGui::Button("Add")) {
    if (strlen(s_name) <= 0) strcpy(s_name, "unnamed");
    if (strlen(s_description) <= 0) strcpy(s_description, "no description");

    _subjects_controller.add_subject(s_name, s_description);
    _subjects_controller.handle_update();
    s_name[0] = '\0';
    s_description[0] = '\0';
    ImGui::CloseCurrentPopup();
    ImGui::EndPopup();
    need_to_draw_add_subject_popup = false;
    return;
  }

  ImGui::SameLine();

  if (ImGui::Button("Cancel")) {
    ImGui::CloseCurrentPopup();
    need_to_draw_add_subject_popup = false;
  }

  ImGui::EndPopup();
}

void ui::draw_edit_subject_popup(subject &s) {
  ImGui::OpenPopup("Edit Subject");
  static char s_name[MAX_SUBJECT_NAME_LEN];
  static char s_description[MAX_SUBJECT_DESCRIPTION_LEN];

  if(s_name[0] == '\0') strcpy(s_name, s.get_name().c_str());
  if(s_description[0] == '\0') strcpy(s_description, s.get_description().c_str());

  if (!ImGui::BeginPopupModal("Edit Subject", nullptr,
                              ImGuiWindowFlags_AlwaysAutoResize)) return;

  ImGui::InputText("Name", s_name, MAX_SUBJECT_NAME_LEN);
  ImGui::InputText("Description", s_description, MAX_SUBJECT_DESCRIPTION_LEN);

  if (ImGui::Button("Save")) {
    if (strlen(s_name) <= 0) strcpy(s_name, "unnamed");
    if (strlen(s_description) <= 0) strcpy(s_description, "no description");

    s.change_name(s_name);
    s.change_description(s_description);

    _subjects_controller.handle_update();
    s_name[0] = '\0';
    s_description[0] = '\0';
    ImGui::CloseCurrentPopup();
    ImGui::EndPopup();
    need_to_draw_edit_subject_popup = false;
    return;
  }

  ImGui::SameLine();

  if (ImGui::Button("Cancel")) {
    ImGui::CloseCurrentPopup();
    need_to_draw_edit_subject_popup = false;
  }

  ImGui::EndPopup();
}

void ui::draw_add_task_popup() {
  ImGui::OpenPopup("Add Task");
  static char t_name[MAX_SUBJECT_NAME_LEN];
  static char t_description[MAX_SUBJECT_DESCRIPTION_LEN];
  static char t_deadline[MAX_SUBJECT_DESCRIPTION_LEN];

  if (!ImGui::BeginPopupModal("Add Task", nullptr,
                              ImGuiWindowFlags_AlwaysAutoResize)) return;

  ImGui::InputText("Name", t_name, MAX_SUBJECT_NAME_LEN);
  ImGui::InputText("Description", t_description, MAX_SUBJECT_DESCRIPTION_LEN);
  ImGui::InputText("Deadline", t_deadline, MAX_SUBJECT_DESCRIPTION_LEN);

  if (ImGui::Button("Add")) {
    if (strlen(t_name) <= 0) strcpy(t_name, "unnamed");
    if (strlen(t_description) <= 0) strcpy(t_description, "no description");
    if (strlen(t_deadline) <= 0) strcpy(t_deadline, "no deadline");

    _subjects_controller.get_subject_by_id(_cur_subject).add_task(t_name, t_description, t_deadline);
    _subjects_controller.handle_update();
    t_name[0] = '\0';
    t_description[0] = '\0';
    t_deadline[0] = '\0';
    ImGui::CloseCurrentPopup();
    ImGui::EndPopup();
    need_to_draw_add_task_popup = false;
    return;
  }

  ImGui::SameLine();

  if (ImGui::Button("Cancel")) {
    ImGui::CloseCurrentPopup();
    need_to_draw_add_task_popup = false;
  }

  ImGui::EndPopup();
}

void ui::draw_edit_task_popup(task &t) {
  ImGui::OpenPopup("Edit Task");
  static char t_name[MAX_SUBJECT_NAME_LEN];
  static char t_description[MAX_SUBJECT_DESCRIPTION_LEN];
  static char t_deadline[MAX_SUBJECT_DESCRIPTION_LEN];
  static float t_progress = 0.0f;

  if(t_name[0] == '\0') strcpy(t_name, t.get_name().c_str());
  if(t_description[0] == '\0') strcpy(t_description, t.get_description().c_str());
  if(t_deadline[0] == '\0') strcpy(t_deadline, t.get_deadline().c_str());
  if (t_progress == 0.0f) t_progress = t.get_readiness() * 100.0f;

  if (!ImGui::BeginPopupModal("Edit Task", nullptr,
                              ImGuiWindowFlags_AlwaysAutoResize)) return;

  ImGui::InputText("Name", t_name, MAX_SUBJECT_NAME_LEN);
  ImGui::InputText("Description", t_description, MAX_SUBJECT_DESCRIPTION_LEN);
  ImGui::InputText("Deadline", t_deadline, MAX_SUBJECT_DESCRIPTION_LEN);
  ImGui::SliderFloat("Progress", &t_progress, 0.0f, 100.0f, "%.0f%%");

  if (ImGui::Button("Save")) {
    if (strlen(t_name) <= 0) strcpy(t_name, "unnamed");
    if (strlen(t_description) <= 0) strcpy(t_description, "no description");
    if (strlen(t_deadline) <= 0) strcpy(t_deadline, "no deadline");

    t.change_name(t_name);
    t.change_description(t_description);
    t.change_deadline(t_deadline);
    t.change_readiness(t_progress / 100.0f);

    _subjects_controller.handle_update();
    t_name[0] = '\0';
    t_description[0] = '\0';
    t_deadline[0] = '\0';
    t_progress = 0.0f;

    ImGui::CloseCurrentPopup();
    ImGui::EndPopup();
    need_to_draw_edit_task_popup = false;
    return;
  }

  ImGui::SameLine();

  if (ImGui::Button("Cancel")) {
    ImGui::CloseCurrentPopup();
    need_to_draw_edit_task_popup = false;
  }

  ImGui::EndPopup();
}

void ui::draw_delete_subject_confirmation_popup() {
  ImGui::OpenPopup("Delete Subject Confirmation");

  if (!ImGui::BeginPopupModal("Delete Subject Confirmation", nullptr,
                              ImGuiWindowFlags_AlwaysAutoResize))
    return;

  ImGui::Text("Are you sure you want to delete this subject?");

  if (ImGui::Button("Yes")) {
    _subjects_controller.remove_subject(_cur_subject);
    _subjects_controller.handle_update();
    need_to_draw_delete_subject_confirmation = false;
    ImGui::CloseCurrentPopup();
  }

  ImGui::SameLine();

  if (ImGui::Button("No")) {
    need_to_draw_delete_subject_confirmation = false;
    ImGui::CloseCurrentPopup();
  }

  ImGui::EndPopup();
}

void ui::draw_delete_task_confirmation_popup() {
  ImGui::OpenPopup("Delete Task Confirmation");

  if (!ImGui::BeginPopupModal("Delete Task Confirmation", nullptr,
                              ImGuiWindowFlags_AlwaysAutoResize))
    return;

  ImGui::Text("Are you sure you want to delete this task?");

  if (ImGui::Button("Yes")) {
    _subjects_controller.get_subject_by_id(_cur_subject).remove_task(_cur_task);
    _subjects_controller.handle_update();
    need_to_draw_delete_task_confirmation = false;
    ImGui::CloseCurrentPopup();
  }

  ImGui::SameLine();

  if (ImGui::Button("No")) {
    need_to_draw_delete_task_confirmation = false;
    ImGui::CloseCurrentPopup();
  }

  ImGui::EndPopup();
}

