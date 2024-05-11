
#ifndef __ACCESS_CONTROL_H__
#define __ACCESS_CONTROL_H__

#include <EEPROM.h>

#define NAME_LENGTH 16

#define ACCESS_ENTRIES 20
#define EEPROM_SIZE ACCESS_ENTRIES * sizeof(AccessEntry)

#define NULL_IDENTIFIER 0
#define INVALID_INDEX 0xFF

static const char * const DEFAULT_NAME = "Unknown";

typedef struct {
    uint16_t identifier;
    char name[NAME_LENGTH+1];
} AccessEntry;

class AccessControl {
private:
    AccessEntry entries[ACCESS_ENTRIES];
    AccessEntry * nextEntry = NULL;
    int nEntries = 0;
    int iteratorIndex = 0;
public:
    AccessControl()
    {
        EEPROM.begin(EEPROM_SIZE);
        
        for (int i = 0; i < ACCESS_ENTRIES; i++)
        {
            entries[i].identifier = NULL_IDENTIFIER;
            strncpy(entries[i].name, DEFAULT_NAME, NAME_LENGTH);
            entries[i].name[NAME_LENGTH] = '\0';
            restoreFromEEPROM(i);
            if(entries[i].identifier != NULL_IDENTIFIER)
            {
                nEntries++;
            }
        }
    }

    bool addEntry(uint16_t identifier, const char *name){

        uint8_t index = findEntry(identifier);

        if(index != INVALID_INDEX)
        {
            return false; // duplicated entry
        }

        index = findEntry(NULL_IDENTIFIER);

        if(index == INVALID_INDEX)
        {
            return false; // no space left
        }

        entries[index].identifier = identifier;
        strncpy(entries[index].name, name, NAME_LENGTH);

        saveToEEPROM(index);

        return true;
    }

    void removeEntry(uint16_t identifier)
    {
        uint8_t index = findEntry(identifier);

        if (index != INVALID_INDEX)
        {
            entries[index].identifier = NULL_IDENTIFIER;
            saveToEEPROM(index);
        }
    }

    void saveToEEPROM(uint8_t index)
    {
        EEPROM.put(index * sizeof(AccessEntry), entries[index]);
        EEPROM.commit();
    }

    void restoreFromEEPROM(uint8_t index)
    {
        EEPROM.get(index * sizeof(AccessEntry), entries[index]);
    }

    bool checkAccess(uint16_t identifier)
    {
        return findEntry(identifier) != INVALID_INDEX;
    }

    String getName(uint16_t identifier)
    {
        uint8_t index = findEntry(identifier);

        if(index != INVALID_INDEX)
        {
            return String(entries[index].name);
        }
        else
        {
            return String(DEFAULT_NAME);
        }
    }

    uint8_t findEntry(uint16_t identifier)
    {
        for (int i = 0; i < ACCESS_ENTRIES; i++)
        {
            if(entries[i].identifier == identifier)
            {
                return i;
            }
        }
        return INVALID_INDEX;
    }

    void printEntries()
    {
        for (int i = 0; i < ACCESS_ENTRIES; i++)
        {
            if(entries[i].identifier == NULL_IDENTIFIER)
            {
                continue;
            }

            Serial.print("Entry ");
            Serial.print(i);
            Serial.print(": ");
            Serial.print(entries[i].identifier);
            Serial.print(" ");
            Serial.println(entries[i].name);
        }
    }

    bool hasNext()
    {
        if(iteratorIndex >= ACCESS_ENTRIES)
        {
            nextEntry = NULL;
            return false;
        }
        
        AccessEntry * entry = &entries[iteratorIndex++];

        if(entry->identifier != NULL_IDENTIFIER)
        {
            nextEntry = entry;
            return true;
        }
        else
        {
            return hasNext();
        }
    }

    AccessEntry * next()
    {
        return nextEntry;
    }

    void resetIterator()
    {
        iteratorIndex = 0;
    }

    int getEntriesCount()
    {
        return nEntries;
    }

    void clearEntries()
    {
        for (int i = 0; i < ACCESS_ENTRIES; i++)
        {
            entries[i].identifier = NULL_IDENTIFIER;
            strncpy(entries[i].name, DEFAULT_NAME, NAME_LENGTH);
            EEPROM.put(i * sizeof(AccessEntry), entries[i]);
        }
        
        EEPROM.commit();
    }
};

#endif /* __ACCESS_CONTROL_H__ */