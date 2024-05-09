/*---------------------------------[INCLUDES]---------------------------------*/
// Arduino
//#include "MemoryFree.h"

// App
#include "App.h"
#include "MenuController.h"
#include "Selector.h"
#include "ScreenFactory.h"
#include "CardReader.h"
#include "AccessControl.h"

/*---------------------------------[PREPROCESSOR DEFS]------------------------*/
/* LCD */
#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 20
#define LCD_ROWS    4

/* Digital Pot */
#define SW_PIN      D0
#define DT_PIN      D3
#define CLK_PIN     D4

/* MRFC522 */
#define SS_PIN      D8
#define RST_PIN     10 //S3

/*---------------------------------[TYPE DEFS]--------------------------------*/

/*---------------------------------[PRIVATE DATA]-----------------------------*/

static MFRC522 mfrc522(SS_PIN, RST_PIN);
static CardReader cardReader(mfrc522);
static AccessControl accessControl;

static LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);
static MenuController *menu;

static Selector selector(CLK_PIN, DT_PIN, SW_PIN);

static InfoModel infoModel;
static String textInput;
static HomeModel homeModel(cardReader, accessControl);

static ScreenFactory<String> textInputSF(&textInput);
static ScreenFactory<HomeModel> homeSF(&homeModel);

CREATE_SCREEN(screen_home   , "HOME" , &homeSF);

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
}

static void sw_lp_event_cb()
{
    menu->TriggerEvent(Event::EV_CANCEL_PRESSED);
}

/*---------------------------------[PUBLIC FUNCTIONS]-------------------------*/

void App_setup()
{
    Serial.println("### APP INIT ###");

    cardReader.init();

    selector.addCallback(Selector::CbType::CCW_CB, ccw_event_cb);
    selector.addCallback(Selector::CbType::CW_CB, cw_event_cb);
    selector.addCallback(Selector::CbType::SW_SP_CB, sw_sp_event_cb);
    selector.addCallback(Selector::CbType::SW_LP_CB, sw_lp_event_cb);

    menu = new MenuController(lcd);

    menu->AddScreen("/home"             , screen_home);

    menu->Enter("/home");
}

void App_loop()
{
    cardReader.run();
    selector.run();
    menu->TriggerEvent(Event::EV_UPDATE_LOOP);
}