/*---------------------------------[INCLUDES]---------------------------------*/
// Arduino
//#include "MemoryFree.h"

// App
#include "App.h"
#include "MenuController.h"
#include "Selector.h"
#include "ScreenFactory.h"

/*---------------------------------[PREPROCESSOR DEFS]------------------------*/

#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 20
#define LCD_ROWS 4

#define SW_PIN      D0
#define DT_PIN      D3
#define CLK_PIN     D4

/*---------------------------------[TYPE DEFS]--------------------------------*/

/*---------------------------------[PRIVATE DATA]-----------------------------*/

static LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);
static MenuController *menu;

static Selector selector(CLK_PIN, DT_PIN, SW_PIN);

static TimeModel timer1(10, 55);
static TimeModel timer2(90, 10);
static WeekModel weekModel;
static InfoModel infoModel;
static String textInput;

static ScreenFactory<TimeModel> t1sf(&timer1);
static ScreenFactory<TimeModel> t2sf(&timer2);
static ScreenFactory<WeekModel> weeksf(&weekModel);
static ScreenFactory<InfoModel> infosf(&infoModel);
static ScreenFactory<String> textInputSF(&textInput);

CREATE_SCREEN(screen_home   , "HOME"        , NULL);
CREATE_SCREEN(screen_p1     , "PUMP 1"      , NULL);
CREATE_SCREEN(screen_p2     , "PUMP 2"      , NULL);
CREATE_SCREEN(screen_in     , "TEXT INPUT"  , &textInputSF);
CREATE_SCREEN(screen_t1     , "On time"     , &t1sf);
CREATE_SCREEN(screen_t2     , "Off time"    , &t2sf);
CREATE_SCREEN(screen_week   , "Select days" , &weeksf);
CREATE_SCREEN(screen_info   , "INFO"        , &infosf);

/*---------------------------------[PRIVATE FUNCTIONS]------------------------*/

static void ccw_event_cb()
{
    menu->TriggerEvent(Event::EV_CCW_STEP);
    Serial.println("CCW_");
}

static void cw_event_cb()
{
    menu->TriggerEvent(Event::EV_CW_STEP);
    Serial.println("CW_");
}

static void sw_sp_event_cb()
{
    menu->TriggerEvent(Event::EV_CONFIRM_PRESSED);
    App_printFreeMemory();
}

static void sw_lp_event_cb()
{
    menu->TriggerEvent(Event::EV_CANCEL_PRESSED);
    App_printFreeMemory();
}


/*---------------------------------[PUBLIC FUNCTIONS]-------------------------*/

void App_setup()
{
    Serial.println("### APP INIT ###");

    App_printFreeMemory();

    selector.addCallback(Selector::CbType::CCW_CB, ccw_event_cb);
    selector.addCallback(Selector::CbType::CW_CB, cw_event_cb);
    selector.addCallback(Selector::CbType::SW_SP_CB, sw_sp_event_cb);
    selector.addCallback(Selector::CbType::SW_LP_CB, sw_lp_event_cb);

    menu = new MenuController(lcd);

    menu->AddScreen("/home"             , screen_home);
    menu->AddScreen("/home/p1"          , screen_p1);
    menu->AddScreen("/home/p1/week"     , screen_week);
    menu->AddScreen("/home/p1/t_on"     , screen_t1);
    menu->AddScreen("/home/p1/t_off"    , screen_t2);
    menu->AddScreen("/home/p2"          , screen_p2);
    menu->AddScreen("/home/p2/week"     , screen_week);
    menu->AddScreen("/home/p2/t_on"     , screen_t1);
    menu->AddScreen("/home/p2/t_off"    , screen_t2);
    menu->AddScreen("/home/info"        , screen_info);
    menu->AddScreen("/home/input"       , screen_in);

    menu->Enter("/home");
    
    App_printFreeMemory();
}

void App_loop()
{
    selector.run();
    timer1.update();
    timer2.update();
    menu->TriggerEvent(Event::EV_UPDATE_LOOP);
}

void App_printFreeMemory()
{
    Serial.print("Free Memory: ");
    //Serial.print(freeMemory());
    Serial.println(" bytes");
}