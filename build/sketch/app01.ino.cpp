#line 1 "C:\\Users\\jlnbo\\Repos\\esp8266\\app01\\app01.ino"
#include <Arduino.h>
#include "src/app/app.h"

#line 4 "C:\\Users\\jlnbo\\Repos\\esp8266\\app01\\app01.ino"
void setup();
#line 11 "C:\\Users\\jlnbo\\Repos\\esp8266\\app01\\app01.ino"
void loop();
#line 4 "C:\\Users\\jlnbo\\Repos\\esp8266\\app01\\app01.ino"
void setup()
{
  Serial.begin(115200);
  Serial.println("Setup INIT");
  App_setup();  
}

void loop()
{
  App_loop();  
}
