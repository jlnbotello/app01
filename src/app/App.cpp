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

static ContainerModel containerModel;
static String textInput = "              "; // this instance should be part of NewCardModel
static HomeModel homeModel(cardReader, accessControl);
static NewCardModel newCardModel(cardReader, accessControl, textInput);
static CardListModel cardListModel(accessControl);

static ScreenFactory<ContainerScreen, ContainerModel> containerSF(&containerModel);
static ScreenFactory<TextInputScreen, String> textInputSF(&textInput);
static ScreenFactory<HomeScreen, HomeModel> homeSF(&homeModel);
static ScreenFactory<NewCardScreen, NewCardModel> newCardSF(&newCardModel);
static ScreenFactory<CardListScreen, CardListModel> cardListSF(&cardListModel);

CREATE_SCREEN(screen_home   , "HOME" , &homeSF);
CREATE_SCREEN(screen_cfg    , "CONFIG" , &containerSF);
CREATE_SCREEN(screen_new    , "Add card" , &newCardSF);
CREATE_SCREEN(screen_list   , "Remove card" , &cardListSF);
CREATE_SCREEN(screen_input  , "Text Input"  , &textInputSF);


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

    pinMode(RELAY_PIN, OUTPUT); // Comment to disable relay and use Serial instead
    digitalWrite(RELAY_PIN, HIGH);

    textInput.clear();
    cardReader.init();

    selector.addCallback(Selector::CbType::CCW_CB, ccw_event_cb);
    selector.addCallback(Selector::CbType::CW_CB, cw_event_cb);
    selector.addCallback(Selector::CbType::SW_SP_CB, sw_sp_event_cb);
    selector.addCallback(Selector::CbType::SW_LP_CB, sw_lp_event_cb);

    menu = new MenuController(lcd);

    menu->AddScreen("/home"             , screen_home);
    menu->AddScreen("/home/cfg"         , screen_cfg);
    menu->AddScreen("/home/cfg/new"     , screen_new);
    menu->AddScreen("/home/cfg/new/name", screen_input);
    menu->AddScreen("/home/cfg/list"    , screen_list);
    
    

    menu->Enter("/home");
}

void App_loop()
{
    selector.run();
    menu->TriggerEvent(Event::EV_UPDATE_LOOP);
}