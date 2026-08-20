#include "StorageManager.h"
#include <LittleFS.h>
#include "../config/Types.h"
#include "../auth/AuthManager.h"

StorageManager storage;

bool StorageManager::begin() {
    return LittleFS.begin();
}

bool StorageManager::writeAtomic(const char* filepath, JsonDocument& doc) {
    String tmpPath = String(filepath) + ".tmp";
    String bakPath = String(filepath) + ".bak";
    
    File file = LittleFS.open(tmpPath, "w");
    if (!file) return false;
    
    if (serializeJson(doc, file) == 0) {
        file.close();
        return false;
    }
    file.close();
    
    // Backup existing
    if (LittleFS.exists(filepath)) {
        if (LittleFS.exists(bakPath)) LittleFS.remove(bakPath);
        LittleFS.rename(filepath, bakPath);
    }
    
    // Rename tmp to official
    bool success = LittleFS.rename(tmpPath, filepath);
    if (!success) {
        // Rollback
        if (LittleFS.exists(bakPath)) {
            LittleFS.rename(bakPath, filepath);
        }
    }
    return success;
}

bool StorageManager::readJson(const char* filepath, JsonDocument& doc) {
    String bakPath = String(filepath) + ".bak";
    File file = LittleFS.open(filepath, "r");
    
    if (!file) {
        // Try backup
        file = LittleFS.open(bakPath, "r");
        if (!file) return false;
    }
    
    DeserializationError error = deserializeJson(doc, file);
    file.close();
    
    if (error) {
        // If main file corrupted, try backup
        if (String(file.fullName()) == filepath) {
            file = LittleFS.open(bakPath, "r");
            if (file) {
                error = deserializeJson(doc, file);
                file.close();
                if (!error) return true;
            }
        }
        return false;
    }
    return true;
}

void StorageManager::migrateLegacyPlayers(const String& content, Player players[], int& playerCount, int& nextPlayerId) {
    playerCount = 0;
    int searchPos = 0;
    while (playerCount < 50) { // MAX_PLAYERS
        int idPos = content.indexOf("\"id\":", searchPos);
        if (idPos == -1) break;

        int idEnd = content.indexOf(",", idPos);
        int id = content.substring(idPos + 5, idEnd).toInt();

        int nomePos = content.indexOf("\"nome\":\"", idEnd);
        int nomeEnd = content.indexOf("\"", nomePos + 8);
        String nome = content.substring(nomePos + 8, nomeEnd);

        int telPos = content.indexOf("\"telefone\":\"", nomeEnd);
        int telEnd = content.indexOf("\"", telPos + 12);
        String tel = content.substring(telPos + 12, telEnd);

        int senPos = content.indexOf("\"senha\":\"", telEnd);
        int senEnd = telEnd;
        String senha = "0000";
        if (senPos != -1) {
            senEnd = content.indexOf("\"", senPos + 9);
            senha = content.substring(senPos + 9, senEnd);
        }

        int eloPos = content.indexOf("\"elo\":", senEnd);
        int eloEnd = content.indexOf(",", eloPos);
        int elo = content.substring(eloPos + 6, eloEnd).toInt();

        int vitPos = content.indexOf("\"vitorias\":", eloEnd);
        int vitEnd = content.indexOf(",", vitPos);
        int vit = content.substring(vitPos + 11, vitEnd).toInt();

        int derPos = content.indexOf("\"derrotas\":", vitEnd);
        int derEnd = content.indexOf("\n", derPos);
        if (derEnd == -1) derEnd = content.indexOf("}", derPos);
        int der = content.substring(derPos + 11, derEnd).toInt();

        int peak = elo;
        int maxStreak = 0;
        int curStreak = 0;
        int titles = 0;
        int shutouts = 0;

        int peakPos = content.indexOf("\"peak_elo\":", derEnd);
        if (peakPos != -1) peak = content.substring(peakPos + 11, content.indexOf(",", peakPos)).toInt();

        int maxSPos = content.indexOf("\"max_win_streak\":", derEnd);
        if (maxSPos != -1) maxStreak = content.substring(maxSPos + 17, content.indexOf(",", maxSPos)).toInt();

        int curSPos = content.indexOf("\"current_streak\":", derEnd);
        if (curSPos != -1) curStreak = content.substring(curSPos + 17, content.indexOf(",", curSPos)).toInt();
        
        int titlesPos = content.indexOf("\"titles_count\":", derEnd);
        if (titlesPos != -1) titles = content.substring(titlesPos + 15, content.indexOf(",", titlesPos)).toInt();
        
        int shutoutsPos = content.indexOf("\"shutout_count\":", derEnd);
        if (shutoutsPos != -1) {
            int shutoutEnd = content.indexOf("\n", shutoutsPos);
            if (shutoutEnd == -1) shutoutEnd = content.indexOf("}", shutoutsPos);
            shutouts = content.substring(shutoutsPos + 16, shutoutEnd).toInt();
        }

        // Migrate PIN hashing
        if (senha.length() == 4) {
            senha = auth.hashPin(senha);
        }

        players[playerCount] = {id, nome, tel, senha, elo, vit, der, peak, maxStreak, curStreak, titles, shutouts};
        if (id >= nextPlayerId) nextPlayerId = id + 1;
        playerCount++;

        searchPos = derEnd;
    }
    savePlayers(players, playerCount); // Save to new schema
}

bool StorageManager::loadPlayers(Player players[], int& playerCount, int& nextPlayerId) {
    if (!LittleFS.exists("/players.json")) {
        playerCount = 0;
        nextPlayerId = 1;
        return savePlayers(players, playerCount);
    }
    
    // Read raw to check schema
    File file = LittleFS.open("/players.json", "r");
    if (!file) return false;
    String content = file.readString();
    file.close();
    
    // Check if it's the new schema (object with version) or old schema (array)
    content.trim();
    if (content.startsWith("[")) {
        // Legacy
        migrateLegacyPlayers(content, players, playerCount, nextPlayerId);
        return true;
    }
    
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, content);
    if (error) return false;
    
    int version = doc["schema_version"] | 1;
    if (version >= 2) {
        JsonArray arr = doc["players"].as<JsonArray>();
        playerCount = 0;
        nextPlayerId = 1;
        for (JsonObject p : arr) {
            if (playerCount >= 50) break;
            
            players[playerCount].id = p["id"];
            players[playerCount].nome = p["nome"].as<String>();
            players[playerCount].telefone = p["telefone"].as<String>();
            players[playerCount].senha = p["senha"].as<String>();
            players[playerCount].elo = p["elo"];
            players[playerCount].vitorias = p["vitorias"];
            players[playerCount].derrotas = p["derrotas"];
            players[playerCount].peak_elo = p["peak_elo"];
            players[playerCount].max_win_streak = p["max_win_streak"];
            players[playerCount].current_streak = p["current_streak"];
            players[playerCount].titles_count = p["titles_count"];
            players[playerCount].shutout_count = p["shutout_count"];
            
            if (players[playerCount].id >= nextPlayerId) {
                nextPlayerId = players[playerCount].id + 1;
            }
            playerCount++;
        }
    }
    return true;
}

bool StorageManager::savePlayers(Player players[], int playerCount) {
    JsonDocument doc;
    doc["schema_version"] = 2;
    JsonArray arr = doc["players"].to<JsonArray>();
    
    for (int i = 0; i < playerCount; i++) {
        JsonObject p = arr.add<JsonObject>();
        p["id"] = players[i].id;
        p["nome"] = players[i].nome;
        p["telefone"] = players[i].telefone;
        p["senha"] = players[i].senha;
        p["elo"] = players[i].elo;
        p["vitorias"] = players[i].vitorias;
        p["derrotas"] = players[i].derrotas;
        p["peak_elo"] = players[i].peak_elo;
        p["max_win_streak"] = players[i].max_win_streak;
        p["current_streak"] = players[i].current_streak;
        p["titles_count"] = players[i].titles_count;
        p["shutout_count"] = players[i].shutout_count;
    }
    
    return writeAtomic("/players.json", doc);
}

bool StorageManager::loadHistory(MatchHistoryItem history[], int& historyCount) {
    if (!LittleFS.exists("/matches.json")) {
        historyCount = 0;
        return true;
    }
    
    File file = LittleFS.open("/matches.json", "r");
    if (!file) return false;
    String content = file.readString();
    file.close();
    
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, content);
    if (error) {
        historyCount = 0;
        return false;
    }
    
    int version = doc["schema_version"] | 1;
    if (version >= 2) {
        JsonArray arr = doc["history"].as<JsonArray>();
        historyCount = 0;
        for (JsonObject m : arr) {
            if (historyCount >= 50) break;
            history[historyCount].id = m["id"];
            history[historyCount].matchType = m["matchType"].as<String>();
            history[historyCount].p1_id = m["p1_id"];
            history[historyCount].p2_id = m["p2_id"];
            history[historyCount].winner_id = m["winner_id"];
            history[historyCount].loser_balls = m["loser_balls"];
            history[historyCount].elo_delta = m["elo_delta"];
            history[historyCount].date_str = m["date_str"].as<String>();
            historyCount++;
        }
    }
    return true;
}

bool StorageManager::saveHistory(MatchHistoryItem history[], int historyCount) {
    JsonDocument doc;
    doc["schema_version"] = 2;
    JsonArray arr = doc["history"].to<JsonArray>();
    
    for (int i = 0; i < historyCount; i++) {
        JsonObject m = arr.add<JsonObject>();
        m["id"] = history[i].id;
        m["matchType"] = history[i].matchType;
        m["p1_id"] = history[i].p1_id;
        m["p2_id"] = history[i].p2_id;
        m["winner_id"] = history[i].winner_id;
        m["loser_balls"] = history[i].loser_balls;
        m["elo_delta"] = history[i].elo_delta;
        m["date_str"] = history[i].date_str;
    }
    
    return writeAtomic("/matches.json", doc);
}
