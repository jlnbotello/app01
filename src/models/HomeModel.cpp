#include "HomeModel.h"

#define EMPTY_STRING "                    " // 20 spaces --> LCD_COLUMNS OR LCD_WIDTH

HomeModel::HomeModel(CardReader & r, AccessControl & ac): cardReader(r), accessControl(ac)
{
    timer.setdelay(3000);
    message = EMPTY_STRING; //TODO: change ugly implementation. make enough big to cover all the row (avoid buffer relocation)
}

HomeModel::~HomeModel()
{

}

const char *HomeModel::get_name()
{
    return "Home";
}

const char *HomeModel::get_time()
{
    return "12:00";
}

const char *HomeModel::get_temperature()
{
    return "25 ºC";
}

const char *HomeModel::get_humidity()
{
    return "50 %";
}

void HomeModel::set_message(String message)
{
    this->message = message;
}

void HomeModel::clear_message()
{
    this->message = EMPTY_STRING;
}

const char *HomeModel::get_message()
{
    return this->message.c_str();
}

void HomeModel::set_cardName(String cardName)
{
    this->cardName = cardName;
}

void HomeModel::clear_cardName()
{
    this->cardName = EMPTY_STRING;
}

const char *HomeModel::get_cardName()
{
    return this->cardName.c_str();
}

bool HomeModel::run()
{
    if (enableCardReading && cardReader.isNewCardPresent())
    {
        enableCardReading = false;
        timer.start();

        uint16_t cardUID = cardReader.getCardUID_2B();

        if(accessControl.checkAccess(cardUID))
        {
            set_cardName(accessControl.getName(cardUID));
            set_message("Access GRANTED  ");
            digitalWrite(RELAY_PIN, LOW);
        }
        else
        {
            set_message("Access DENIED   ");
        }

        return true;        
    }

    if(timer.update())
    {
        timer.stop();
        enableCardReading = true;
        clear_cardName();
        set_message("No card detected");
        digitalWrite(RELAY_PIN, HIGH);
        return true;    
    }
    return false;
}