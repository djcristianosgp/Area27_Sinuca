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
    void migrateLegacyPlayers(const String& content, Player players[], int& playerCount, int& nextPlayerId);
    void createBackup(const char* filepath);

public:
    bool begin();
    
    bool loadPlayers(Player players[], int& playerCount, int& nextPlayerId);
    bool savePlayers(Player players[], int playerCount);
    
    bool loadHistory(MatchHistoryItem history[], int& historyCount);
    bool saveHistory(MatchHistoryItem history[], int historyCount);
};

extern StorageManager storage;

#endif
