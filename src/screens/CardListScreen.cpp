/*---------------------------------[INCLUDES]---------------------------------*/
#include "CardListScreen.h"
#include "AccessControl.h"

/*---------------------------------[PREPROCESSOR DEFS]------------------------*/

/*---------------------------------[TYPE DEFS]--------------------------------*/

/*---------------------------------[PRIVATE DATA]-----------------------------*/

/*---------------------------------[PRIVATE FUNCTIONS]------------------------*/
static void stub(){};

/*---------------------------------[PUBLIC FUNCTIONS]-------------------------*/
CardListScreen::CardListScreen(MenuController &c, CardListModel &m) : model(m), Screen(c)
{
    
    entries = new AccessEntry*[ACCESS_ENTRIES];

    model.accessControl.resetIterator();
    int i=0;

    while(model.accessControl.hasNext() && (i < ACCESS_ENTRIES))
    {
        entries[i] = model.accessControl.next();
        LiquidLine * line_p1 = new LiquidLine(1, i, entries[i]->identifier, " ", DYN_LINE(entries[i]->name));

        line_p1->attach_function(1, stub);
        addLine(line_p1);

        i++;
    }

    m_menu->get_currentScreen()->set_displayLineCount(4); // TODO: create a macro to define the display line count
    m_menu->get_currentScreen()->set_focusPosition(Position::LEFT);
    m_menu->set_focusedLine(0);
    update();
}

CardListScreen::~CardListScreen()
{
  delete[] entries;
}

bool CardListScreen::onEvent(Event event)
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

bool CardListScreen::ev_cw_step()
{
  m_menu->switch_focus(true);
  update();
  return true;
};

bool CardListScreen::ev_ccw_step()
{
  m_menu->switch_focus(false);
  update();
  return true;
};

bool CardListScreen::ev_confirm_pressed()
{
  uint8_t focused = m_menu->get_focusedLine();
  //Serial.print("Removing entry: ");
  //Serial.println(focused);
  //Serial.println(entries[focused]->identifier);
  model.accessControl.removeEntry(entries[focused]->identifier);
  entries[focused]->identifier = NULL_IDENTIFIER;
  strcpy(entries[focused]->name, "Removed...");
  update();

  return true;
};

bool CardListScreen::ev_cancel_pressed()
{
  m_controller.Back();
  return true;
};

bool CardListScreen::ev_update()
{
  return true;
};