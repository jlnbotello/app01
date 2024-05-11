#ifndef __MENU_CONTROLLER_H__
#define __MENU_CONTROLLER_H__

#include "MenuServices.h"

class Screen;
typedef struct ScreenHandlerStruct ScreenHandler;

#define MAX_LINES_PER_SCREEN 4

class MenuController
{
public:
  MenuController(DisplayClass &lcd);
  void AddScreen(const char* url, const ScreenHandler & screen);
  Services * GetServices();
  bool Enter(const char* url);
  bool EnterChild(const char* tag);
  bool Back();
  void TriggerEvent(Event event);

private:
  bool url_remove_last_tag(char* url, size_t maxUrlSize);

  Services m_services;
  Screen * m_current_screen = nullptr;
};

#endif /* __MENU_CONTROLLER_H__ */