# 1 "C:\\Users\\jlnbo\\Repos\\esp8266\\app01\\app01.ino"
# 2 "C:\\Users\\jlnbo\\Repos\\esp8266\\app01\\app01.ino" 2
# 3 "C:\\Users\\jlnbo\\Repos\\esp8266\\app01\\app01.ino" 2

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
