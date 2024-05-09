#ifndef __CARDREADER_H__
#define __CARDREADER_H__

#include <SPI.h>
#include <MFRC522.h>
#include <String>

class CardReader
{
public:
    CardReader(MFRC522 & instance) : mfrc522(instance)
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
            printUID();   
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

    uint32_t getCardUID(void)
    {
        if(mfrc522.uid.size == 4)
        {
            return mfrc522.uid.uidByte[0] << 24 | mfrc522.uid.uidByte[1] << 16 | mfrc522.uid.uidByte[2] << 8 | mfrc522.uid.uidByte[3];
        }

        return 0; // 7 and 10 bytes cards support is not implemented
    }

private:
    MFRC522 & mfrc522;
};

#endif /*__CARDREADER_H__*/