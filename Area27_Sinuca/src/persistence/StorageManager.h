#ifndef STORAGE_MANAGER_H
#define STORAGE_MANAGER_H

#include <Arduino.h>
#include <ArduinoJson.h>

class Player;
class MatchHistoryItem;
class SeasonRecord;

class StorageManager {
private:
    bool writeAtomic(const char* filepath, JsonDocument& doc);
    bool readJson(const char* filepath, JsonDocument& doc);
    void migrateLegacyPlayers(const String& content);
    void createBackup(const char* filepath);

public:
    bool begin();
    
    bool loadPlayers();
    bool savePlayers();
    
    bool loadHistory();
    bool saveHistory();
};

extern StorageManager storage;

#endif
