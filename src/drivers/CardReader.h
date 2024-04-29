#include <SPI.h>
#include <MFRC522.h>

class CardReader
{
public:
    CardReader(MFRC522 instance) : mfrc522(instance)
    {
   
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

private:
    MFRC522 & mfrc522;
};