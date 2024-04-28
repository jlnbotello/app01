#ifndef __TEXT_INPUT_SCREEN__
#define __TEXT_INPUT_SCREEN__

#include "Screen.h"

class TextInputScreen : public Screen
{
public:
    TextInputScreen(MenuController &c, String &m);
    ~TextInputScreen() override;
    bool onEvent(Event event);

private:
    bool ev_cw_step();
    bool ev_ccw_step();
    bool ev_confirm_pressed();
    bool ev_cancel_pressed();
    bool ev_update();

    String &model;
};

#endif // __TEXT_INPUT_SCREEN__