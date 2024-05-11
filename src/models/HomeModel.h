#ifndef __HOMEMODEL_H__
#define __HOMEMODEL_H__

#include <WString.h>
#include "CardReader.h"
#include "NoDelay.h"
#include "AccessControl.h"

#define RELAY_PIN 1 // TX pin. To use the Serial port comment pinMode(RELAY_PIN, OUTPUT)

class HomeModel
{
  String message;
  String cardName = "                    ";
  CardReader & cardReader;
  bool enableCardReading = true;
  noDelay timer; // 2 seconds
  AccessControl & accessControl;

public:


  HomeModel(CardReader & r, AccessControl & ac);
  ~HomeModel();

  const char *get_name();
  const char *get_time();
  const char *get_temperature();
  const char *get_humidity();
  void set_message(String message);
  void clear_message();
  const char *get_message();
  void set_cardName(String cardName);
  const char *get_cardName();
  void clear_cardName();
  bool run();
};

#endif /*__HOMEMODEL_H__*/