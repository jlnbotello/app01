#ifndef __HOME_SCREEN_H__
#define __HOME_SCREEN_H__

#include "Screen.h"
#include "HomeModel.h"

class HomeScreen : public Screen
{
public:  
  HomeScreen(MenuController &c, HomeModel &m);
  ~HomeScreen() override;
  bool onEvent(Event event);

private:
  bool ev_cw_step();
  bool ev_ccw_step();
  bool ev_confirm_pressed();
  bool ev_cancel_pressed();
  bool ev_update();

  HomeModel &model;
};

#endif /*__HOME_SCREEN_H__*/