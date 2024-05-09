#ifndef __SCREEN_FACTORY_H__
#define __SCREEN_FACTORY_H__

#include "TimeScreen.h"
#include "WeekScreen.h"
#include "ContainerScreen.h"
#include "InfoScreen.h"
#include "TextInputScreen.h"
#include "HomeScreen.h"

class ScreenWrapper {
    Screen* screen;

public:
    ScreenWrapper(MenuController &c, void* controller) {
        screen = new ContainerScreen(c);
    }

    ScreenWrapper(MenuController &c, WeekModel* m) {
        screen = new WeekScreen(c, *m);
    }

    ScreenWrapper(MenuController &c, TimeModel *m) {
        screen = new TimeScreen(c, *m);
    }

    ScreenWrapper(MenuController &c, InfoModel *m) {
        screen = new InfoScreen(c, *m);
    }

    ScreenWrapper(MenuController &c, String *m) {
        screen = new TextInputScreen(c, *m);
    }

    ScreenWrapper(MenuController &c, HomeModel *m) {
        screen = new HomeScreen(c, *m);
    }

    /* Add more constuctor here */

    Screen* getScreen() {
        return screen;
    }
};

class ScreenFactoryInterface
{
public:
    virtual Screen* createScreen(MenuController &c) = 0;
};

template <typename T>
class ScreenFactory: public ScreenFactoryInterface{
    T* model = nullptr;
public:
    ScreenFactory(T * m): model(m){};
    
    Screen* createScreen(MenuController &c) override 
    {
        ScreenWrapper wrapper(c, model);
        return wrapper.getScreen();
    }

    ScreenFactoryInterface * factory()
    {
        return (ScreenFactoryInterface *) this;
    }
};

struct ScreenHandlerStruct
{
  const char * title;  
  ScreenFactoryInterface * factory;
};

typedef struct ScreenHandlerStruct ScreenHandler;

#define CREATE_SCREEN(VarName, title, factory) \
static const char VarName ## _Title[] PROGMEM = title; \
static const ScreenHandler VarName = {VarName ## _Title, (ScreenFactoryInterface *) factory}

#endif /* __SCREEN_FACTORY_H__ */