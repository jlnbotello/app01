/*---------------------------------[INCLUDES]---------------------------------*/
#include "TextInputScreen.h"

/*---------------------------------[PRIVATE]----------------------------------*/

bool TextInputScreen::ev_cw_step() {
    // Implementation for clockwise step event
    return true;
}

bool TextInputScreen::ev_ccw_step() {
    // Implementation for counter-clockwise step event
    return true;
}

bool TextInputScreen::ev_confirm_pressed() {
    // Implementation for confirm button pressed event
    return true;
}

bool TextInputScreen::ev_cancel_pressed() {
    m_controller.Back();
    return true;
}

bool TextInputScreen::ev_update() {
    // Implementation for update event
    return true;
}

/*---------------------------------[PUBLIC FUNCTIONS]-------------------------*/

TextInputScreen::TextInputScreen(MenuController &c, String &m) : Screen(c), model(m)
{

    LiquidLine *pInputLine      = new LiquidLine(0, 0, ">", "HOMER SIMPSON");
    LiquidLine *pABCLine        = new LiquidLine(0, 1, "ABCDEFGHIJKLMNOPQRST");
    LiquidLine *pSelectorLine   = new LiquidLine(0, 2, "ʌ");
    LiquidLine *p123Line        = new LiquidLine(0, 3, "UVWXYZ0123456789 DEL");

    addLine(pInputLine);
    addLine(pABCLine);
    addLine(pSelectorLine);
    addLine(p123Line);

    update();    
}

TextInputScreen::~TextInputScreen() 
{
    // Destructor implementation
}

bool TextInputScreen::onEvent(Event event) {
    // Implementation to handle events
    switch (event) {
        case Event::EV_CW_STEP:
            return ev_cw_step();
        case Event::EV_CCW_STEP:
            return ev_ccw_step();
        case Event::EV_CONFIRM_PRESSED:
            return ev_confirm_pressed();
        case Event::EV_CANCEL_PRESSED:
            return ev_cancel_pressed();
        default:
            return false;
    }
}