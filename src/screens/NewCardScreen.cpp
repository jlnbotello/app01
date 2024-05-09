/*---------------------------------[INCLUDES]---------------------------------*/
#include "NewCardScreen.h"

/*---------------------------------[PREPROCESSOR DEFS]------------------------*/

/*---------------------------------[TYPE DEFS]--------------------------------*/

/*---------------------------------[PRIVATE DATA]-----------------------------*/

/*---------------------------------[PRIVATE FUNCTIONS]------------------------*/

static void stub(){};

/*---------------------------------[PUBLIC FUNCTIONS]-------------------------*/
NewCardScreen::NewCardScreen(MenuController &c, NewCardModel &m) : model(m), Screen(c)
{
  LiquidLine *pTitle   = new LiquidLine(0, 0, ">>    New card    <<");
  LiquidLine *pUser    = new LiquidLine(1, 1, "Name: ", DYN_LINE(model.get_username()));  
  LiquidLine *pCard    = new LiquidLine(1, 2, "Card: ", DYN_LINE(model.get_cardId()));
  LiquidLine *pConfirm = new LiquidLine(1, 3, "Confirm");  

  pUser->attach_function(1, stub);
  pConfirm->attach_function(1, stub);

  addLine(pTitle);
  addLine(pUser);
  addLine(pCard);
  addLine(pConfirm);

  m_menu->get_currentScreen()->set_focusPosition(Position::LEFT);
  m_menu->set_focusedLine(1);

  if(model.textInput.length() == 0)
  {
    model.set_username("<name>       ");
  }
  else
  {
    model.set_username(model.textInput);
  }
}

NewCardScreen::~NewCardScreen()
{
  model.textInput.clear();
}

bool NewCardScreen::onEvent(Event event)
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
    update();
    break;

  case EV_CW_STEP:
    ev_cw_step();
    update();
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

bool NewCardScreen::ev_cw_step()
{
  m_menu->switch_focus(true);
  
  return true;
};

bool NewCardScreen::ev_ccw_step()
{
  m_menu->switch_focus(false);

  return true;
};

bool NewCardScreen::ev_confirm_pressed()
{
  uint8_t focused = m_menu->get_focusedLine();

  if(focused == 1) // Name
  {
    m_controller.Enter("/home/cfg/new/name");
  }
  else if(focused == 3) // Confirm
  {
    model.addNewCard();
    m_controller.Back();
  }
  
  return true;
};

bool NewCardScreen::ev_cancel_pressed()
{
  m_controller.Back();
  return true;
};

bool NewCardScreen::ev_update()
{
  if(model.run())
  {
    update();
  }
  return true;
};