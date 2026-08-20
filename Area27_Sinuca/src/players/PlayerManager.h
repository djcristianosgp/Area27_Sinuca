#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include "../config/Types.h"
#include "../auth/AuthManager.h"
#include "../persistence/StorageManager.h"

class PlayerManager {
public:
    static const int MAX_PLAYERS = 50;

    Player players[MAX_PLAYERS];
    int playerCount = 0;
    int nextPlayerId = 1;

    void begin();

    // JSON Serialization
    String getPlayersJSON();

    // Persistence (delegated to StorageManager)
    void save();
    void load();

    // HTTP Route Handlers
    void handleGetPlayers(ESP8266WebServer& server);
    void handlePostPlayers(ESP8266WebServer& server);
    void handleDeletePlayer(ESP8266WebServer& server);
    void handleResetPlayerPassword(ESP8266WebServer& server);
    void handleClearPlayers(ESP8266WebServer& server);
    void handleLoginPlayer(ESP8266WebServer& server);

    // Helpers
    Player* findById(int id);
};

extern PlayerManager playerMgr;

#endif // PLAYER_MANAGER_H
