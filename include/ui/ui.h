#ifndef UI_H
#define UI_H
#include <SDL.h>
#include <subjects_controller.h>

class ui {
private:
  subjects_controller& _subjects_controller;

public:
  explicit ui(subjects_controller& subjects_controller);
  ~ui();

  void draw() const;

};


#endif //UI_H
