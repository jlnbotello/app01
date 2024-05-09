#ifndef __NEW_CARD_SCREEN_H__
#define __NEW_CARD_SCREEN_H__

#include "Screen.h"
#include "NewCardModel.h"
#include "TextInputScreen.h"

class NewCardScreen : public Screen
{
public:  
  NewCardScreen(MenuController &c, NewCardModel &m);
  ~NewCardScreen() override;
  bool onEvent(Event event);

private:
  bool ev_cw_step();
  bool ev_ccw_step();
  bool ev_confirm_pressed();
  bool ev_cancel_pressed();
  bool ev_update();

  NewCardModel &model;
};

#endif /*__NEW_CARD_SCREEN_H__*/