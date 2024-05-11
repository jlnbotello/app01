#ifndef __SCREEN_FACTORY_H__
#define __SCREEN_FACTORY_H__

#include "TimeScreen.h"
#include "WeekScreen.h"
#include "ContainerScreen.h"
#include "InfoScreen.h"
#include "TextInputScreen.h"
#include "HomeScreen.h"
#include "NewCardScreen.h"
#include "CardListScreen.h"

class ScreenFactoryInterface
{
public:
    virtual Screen* createScreen(MenuController &c) = 0;
};

template <typename ScreenType, typename ModelType>
class ScreenFactory: public ScreenFactoryInterface{
    ModelType* model = nullptr;
public:
    ScreenFactory(ModelType * m): model(m){};
    
    Screen* createScreen(MenuController &c) override 
    {
        //ScreenWrapper wrapper(c, model);
        return new ScreenType(c, *model);
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