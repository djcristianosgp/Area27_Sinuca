#ifndef MATCH_MANAGER_H
#define MATCH_MANAGER_H

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include "../config/Types.h"
#include "../auth/AuthManager.h"
#include "../persistence/StorageManager.h"
#include "../players/PlayerManager.h"

class MatchManager {
public:
    static const int MAX_HISTORY = 50;
    
    ActiveMatch activeMatch;
    MatchHistoryItem matchHistory[MAX_HISTORY];
    int matchHistoryCount = 0;

    MatchManager();
    void begin();

    // Helpers
    String generateMatchCode();
    void updateMatchStatus();
    
    // JSON Serialization
    String getHistoryJSON();

    // Persistence (delegated to StorageManager)
    void save();
    void load();

    // HTTP Route Handlers
    void handleCreateMatch(ESP8266WebServer& server);
    void handleJoinMatch(ESP8266WebServer& server);
    void handleRespondInvite(ESP8266WebServer& server);
    void handleGetActiveMatch(ESP8266WebServer& server);
    void handleFinishMatch(ESP8266WebServer& server);
    void handleCancelMatch(ESP8266WebServer& server);
    
    // Routine Check
    void loop();
};

extern MatchManager matchMgr;

// Global helper declarations
extern bool checkAuthAny(ESP8266WebServer& server);

#endif // MATCH_MANAGER_H
