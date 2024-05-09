#ifndef __TEMPLATE_SCREEN_H__
#define __TEMPLATE_SCREEN_H__

/**
 * Instructions:
 *  - Repleace __TEMPLATE_SCREEN_H__ with __YOUR_SCREEN_NAME_H__
 *  - Replace TemplateModel with your own data model. You can also include the model.
 *  - Replace TemplateScreen with your own screen name
 */

#include "Screen.h"

typedef uint8_t TemplateModel; // Create your own data model

class TemplateScreen : public Screen
{
public:  
  TemplateScreen(MenuController &c, TemplateModel &m);
  ~TemplateScreen() override;
  bool onEvent(Event event);

private:
  bool ev_cw_step();
  bool ev_ccw_step();
  bool ev_confirm_pressed();
  bool ev_cancel_pressed();
  bool ev_update();

  TemplateModel &model;
};

#endif /*__TEMPLATE_SCREEN_H__*/