#line 1 "C:\\Users\\jlnbo\\Repos\\esp8266\\app01\\src\\lib\\ContainerScreen.h"
#ifndef __CONTAINER_SCREEN_H__
#define __CONTAINER_SCREEN_H__

#include "Screen.h"

class ContainerScreen : public Screen
{
public:  
  ContainerScreen(MenuController &c);

  bool update();
  bool onEvent(Event event) override;

private:
  bool ev_cw_step() ;
  bool ev_ccw_step() ;
  bool ev_confirm_pressed() ;
  bool ev_cancel_pressed() ;

  int8_t m_focused_line = 0;
  uint8_t m_n_of_lines = 0;
};

#endif /* __CONTAINER_SCREEN_H__ */