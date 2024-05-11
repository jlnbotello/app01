/*---------------------------------[INCLUDES]---------------------------------*/
#include "HomeScreen.h"

/*---------------------------------[PREPROCESSOR DEFS]------------------------*/

/*---------------------------------[TYPE DEFS]--------------------------------*/

/*---------------------------------[PRIVATE DATA]-----------------------------*/

/*---------------------------------[PRIVATE FUNCTIONS]------------------------*/

/*---------------------------------[PUBLIC FUNCTIONS]-------------------------*/
HomeScreen::HomeScreen(MenuController &c, HomeModel &m) : model(m), Screen(c)
{  
  //LiquidLine *pDatetime   = new LiquidLine(0, 0, "09 May 2024    14:08");
  LiquidLine *pWelcome   = new LiquidLine(0, 0, "WELCOME");
  LiquidLine *pName      = new LiquidLine(0, 1, DYN_LINE(model.get_cardName()));  
  LiquidLine *pMsg       = new LiquidLine(0, 3, DYN_LINE(model.get_message()));

  //addLine(pDatetime);
  addLine(pWelcome);
  addLine(pName);
  addLine(pMsg);
}

HomeScreen::~HomeScreen()
{

}

bool HomeScreen::onEvent(Event event)
{
  switch (event)
  {
  case EV_CONFIRM_PRESSED:
    ev_confirm_pressed();
    break;

  case EV_CANCEL_PRESSED:
    ev_cancel_pressed();
    break;

  case EV_CCW_STEP:
    ev_ccw_step();
    break;

  case EV_CW_STEP:
    ev_cw_step();
    break;

  case EV_UPDATE_LOOP:
    ev_update();
    break;

  default:
    return false;
    break;
  }
  return true;
}

bool HomeScreen::ev_cw_step()
{

  update();
  return true;
};

bool HomeScreen::ev_ccw_step()
{

  update();
  return true;
};

bool HomeScreen::ev_confirm_pressed()
{
  m_controller.Enter("/home/cfg");
  return true;
};

bool HomeScreen::ev_cancel_pressed()
{
  m_controller.Back();
  return true;
};

bool HomeScreen::ev_update()
{
  if(model.run())
  {
    update();
  }
  return true;
};