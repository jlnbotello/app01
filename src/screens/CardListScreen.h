#ifndef __CARD_LIST_H__
#define __CARD_LIST_H__

#include "Screen.h"
#include "AccessControl.h"

class CardListModel
{
public:
  CardListModel(AccessControl &ac) : accessControl(ac){};
  
  AccessControl &accessControl;
};


class CardListScreen : public Screen
{
public:  
  CardListScreen(MenuController &c, CardListModel &m);
  ~CardListScreen() override;
  bool onEvent(Event event);

private:
  bool ev_cw_step();
  bool ev_ccw_step();
  bool ev_confirm_pressed();
  bool ev_cancel_pressed();
  bool ev_update();

  CardListModel &model;
  AccessEntry ** entries;
};

#endif /*__CARD_LIST_H__*/