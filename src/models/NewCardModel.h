#ifndef __NEW_CARD_MODEL_H__
#define __NEW_CARD_MODEL_H__

#include "CardReader.h"
#include "NoDelay.h"
#include "AccessControl.h"

class NewCardModel {

private:
    CardReader & cardReader;
    bool enableCardReading = true;
    noDelay timer;
    AccessControl & accessControl;

public:
    NewCardModel(CardReader & r, AccessControl & ac, String & s): cardReader(r), accessControl(ac), textInput(s){
        timer.setdelay(1000); // 1 seconds (1000ms)
    };
    ~NewCardModel(){};

    const char *get_username() {
        return _username.c_str();
    }

    const char *get_cardId() {
        return _cardId.c_str();
    }

    String get_usernameStr() {
        return _username;
    }

    void set_username(String username) {
        _username = username;
    }

    void set_cardId(String cardId) {
        _cardId = cardId;
    }

    bool run(){
        if (enableCardReading && cardReader.isNewCardPresent())
        {
            enableCardReading = false;
            timer.start();

            _cardId.clear();
            _cardId.concat(cardReader.getCardUID_Str());
            _cardId2B = cardReader.getCardUID_2B();

            return true;        
        }

        if(timer.update())
        {
            timer.stop();
            enableCardReading = true;
            return true;    
        }

        return false;
    }

    void addNewCard(){
        
        accessControl.addEntry(_cardId2B, _username.c_str());
    }

    String & textInput;

private:
    String _username = "<name>       ";
    String _cardId   = "<card>       ";
    uint16_t _cardId2B   = 0;
};

#endif /*__NEW_CARD_MODEL_H__*/