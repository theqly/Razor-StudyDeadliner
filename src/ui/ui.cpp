#include "ui/ui.h"
#include <imgui.h>

ui::ui(subjects_controller &subjects_controller)
    : _subjects_controller(subjects_controller) {}
ui::~ui() {}

void ui::draw() const {
  static char subjectName[128] = "";

  ImGui::Begin("Manage subjects");

  ImGui::InputText("Subject name", subjectName, sizeof(subjectName));

  if (ImGui::Button("Add subject")) {
    if (strlen(subjectName) > 0) {
      _subjects_controller.add_subject(subjectName);
      subjectName[0] = '\0';
    }
  }

  ImGui::Separator();

  for (auto &subj : _subjects_controller.get_subjects()) {
    ImGui::Text("ID: %d, Name: %s, Readiness: %.2f%%", subj.get_id(),
                subj.get_name().c_str(), subj.get_readiness() * 100.0f);

    if (ImGui::Button(("Add task##" + std::to_string(subj.get_id())).c_str())) {
      subj.add_task("name", "desc", "deadline");
    }
  }

  if (ImGui::Button("Save")) {
    _subjects_controller.get_file_manager().save(_subjects_controller.get_subjects());
  }

  ImGui::End();
}
