#include <SPI.h>
#include <MFRC522.h>

#include "AccessControl.h"
#include <String>

#define DELETE_TAG  "A9 CB 7A 48"
#define ADD_TAG     "36 6C E8 F7"
#define PRINT_TAG   "E9 A3 73 48"

class CardReader
{
public:
    CardReader(MFRC522 & instance) : mfrc522(instance), accessControl(*(new AccessControl()))
    {
   
    }

    void init(void)
    {
        SPI.begin();        // Init SPI bus
        mfrc522.PCD_Init(); // Init MFRC522
    }

    bool isNewCardPresent()
    {
        // Look for new cards
        if ( ! mfrc522.PICC_IsNewCardPresent()) 
        {
            return false;
        }
        // Select one of the cards
        if ( ! mfrc522.PICC_ReadCardSerial()) 
        {
            return false;
        }
        return true;
    }

    MFRC522::Uid getDetectedCardUID(void)
    {
        return mfrc522.uid;
    }

    void printUID(void)
    {
        Serial.print("UID Tag: ");

        for (byte i = 0; i < mfrc522.uid.size; i++) 
        {
            Serial.print(" ");
            Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
            Serial.print(mfrc522.uid.uidByte[i], HEX);
        }

        Serial.println();
    }

    void run(void)
    {
        if (isNewCardPresent())
        {         
            if(isUID(DELETE_TAG) && status != 1)
            {
                Serial.println("Delete Tag");
                status = 1;
                accessControl.clearEntries();
            }

            if(isUID(ADD_TAG) && status != 2)
            {
                Serial.println("Add Tag");
                status = 2;
                uint16_t uid = mfrc522.uid.uidByte[0] << 8 | mfrc522.uid.uidByte[1];
                accessControl.addEntry(uid, "Test");
            }

            if(isUID(PRINT_TAG) && status != 3)
            {
                Serial.println("Print Tag");
                status = 3;
                accessControl.printEntries();
            }
        }
    }

    bool isUID(const char * uidStr)
    {
        String content= "";
        
        for (byte i = 0; i < mfrc522.uid.size; i++) 
        {
            content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
            content.concat(String(mfrc522.uid.uidByte[i], HEX));
        }

        content.toUpperCase();

        if (content.substring(1) == uidStr) //change UID of the card that you want to give access
        {
            return true;
        }

        return false;
    }

private:
    MFRC522 & mfrc522;
    AccessControl & accessControl;
    uint8_t status = 0;
};