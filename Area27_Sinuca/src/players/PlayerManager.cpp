#include "PlayerManager.h"
#include <ArduinoJson.h>

PlayerManager playerMgr;

// Forward declared helpers from AuthManager
extern bool checkAuthAdmin(ESP8266WebServer& server);

void PlayerManager::begin() {
    load();
}

Player* PlayerManager::findById(int id) {
    for (int i = 0; i < playerCount; i++) {
        if (players[i].id == id) return &players[i];
    }
    return nullptr;
}

void PlayerManager::save() {
    storage.savePlayers(players, playerCount);
}

void PlayerManager::load() {
    storage.loadPlayers(players, playerCount, nextPlayerId);
}

String PlayerManager::getPlayersJSON() {
    String json = "[\n";
    for (int i = 0; i < playerCount; i++) {
        json += "  {\n";
        json += "    \"id\":" + String(players[i].id) + ",\n";
        json += "    \"nome\":\"" + players[i].nome + "\",\n";
        json += "    \"telefone\":\"" + players[i].telefone + "\",\n";
        json += "    \"elo\":" + String(players[i].elo) + ",\n";
        json += "    \"vitorias\":" + String(players[i].vitorias) + ",\n";
        json += "    \"derrotas\":" + String(players[i].derrotas) + ",\n";
        json += "    \"peak_elo\":" + String(players[i].peak_elo) + ",\n";
        json += "    \"max_win_streak\":" + String(players[i].max_win_streak) + ",\n";
        json += "    \"current_streak\":" + String(players[i].current_streak) + ",\n";
        json += "    \"titles_count\":" + String(players[i].titles_count) + ",\n";
        json += "    \"shutout_count\":" + String(players[i].shutout_count) + "\n";
        json += "  }";
        if (i < playerCount - 1) json += ",";
        json += "\n";
    }
    json += "]";
    return json;
}

void PlayerManager::handleGetPlayers(ESP8266WebServer& server) {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "application/json", getPlayersJSON());
}

void PlayerManager::handlePostPlayers(ESP8266WebServer& server) {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    if (!checkAuthAdmin(server)) return;
    if (!server.hasArg("plain")) {
        server.send(400, "application/json", "{\"error\":\"Body ausente\"}");
        return;
    }

    String body = server.arg("plain");
    JsonDocument doc;
    DeserializationError err = deserializeJson(doc, body);
    if (err) {
        server.send(400, "application/json", "{\"error\":\"JSON inválido\"}");
        return;
    }

    String nome = doc["nome"] | "";
    if (nome.length() == 0) {
        server.send(400, "application/json", "{\"error\":\"Nome obrigatório\"}");
        return;
    }
    String telefone = doc["telefone"] | "";
    String senha    = doc["senha"] | "0000";

    if (playerCount < MAX_PLAYERS) {
        int newId = nextPlayerId++;
        // Hash the PIN before storing
        String hashedPin = auth.hashPin(senha);
        players[playerCount] = {newId, nome, telefone, hashedPin, 1000, 0, 0, 1000, 0, 0, 0, 0};
        playerCount++;
        save();
        server.send(201, "application/json",
            "{\"success\":true,\"id\":" + String(newId) +
            ",\"nome\":\"" + nome +
            "\",\"telefone\":\"" + telefone + "\"}");
    } else {
        server.send(400, "application/json", "{\"error\":\"Limite de jogadores atingido\"}");
    }
}

void PlayerManager::handleLoginPlayer(ESP8266WebServer& server) {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    if (!server.hasArg("plain")) {
        server.send(400, "application/json", "{\"error\":\"Body ausente\"}");
        return;
    }

    String body = server.arg("plain");
    JsonDocument doc;
    DeserializationError err = deserializeJson(doc, body);
    if (err) {
        server.send(400, "application/json", "{\"error\":\"JSON inválido\"}");
        return;
    }

    String telefone = doc["telefone"] | "";
    int    idVal    = doc["id"] | 0;
    String senha    = doc["senha"] | "";

    Player* matched = nullptr;
    for (int i = 0; i < playerCount; i++) {
        if ((idVal > 0 && players[i].id == idVal) ||
            (telefone.length() > 0 && players[i].telefone == telefone)) {
            matched = &players[i];
            break;
        }
    }

    String token;
    if (matched && auth.loginPlayer(matched->id, senha, matched->senha, token)) {
        server.send(200, "application/json",
            "{\"success\":true,\"token\":\"" + token +
            "\",\"player\":{\"id\":" + String(matched->id) +
            ",\"nome\":\"" + matched->nome +
            "\",\"telefone\":\"" + matched->telefone +
            "\",\"elo\":" + String(matched->elo) + "}}");
    } else {
        server.send(401, "application/json", "{\"error\":\"Telefone ou PIN incorreto\"}");
    }
}

void PlayerManager::handleDeletePlayer(ESP8266WebServer& server) {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    if (!checkAuthAdmin(server)) return;
    if (!server.hasArg("plain")) return;

    String body = server.arg("plain");
    JsonDocument doc;
    if (deserializeJson(doc, body) || !doc["id"].is<int>()) {
        server.send(400, "application/json", "{\"error\":\"id ausente\"}");
        return;
    }
    int targetId = doc["id"];

    int targetIndex = -1;
    for (int i = 0; i < playerCount; i++) {
        if (players[i].id == targetId) { targetIndex = i; break; }
    }

    if (targetIndex != -1) {
        for (int i = targetIndex; i < playerCount - 1; i++) players[i] = players[i + 1];
        playerCount--;
        save();
        server.send(200, "application/json", "{\"success\":true,\"message\":\"Jogador excluído\"}");
    } else {
        server.send(404, "application/json", "{\"error\":\"Jogador não encontrado\"}");
    }
}

void PlayerManager::handleResetPlayerPassword(ESP8266WebServer& server) {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    if (!checkAuthAdmin(server)) return;
    if (!server.hasArg("plain")) return;

    String body = server.arg("plain");
    JsonDocument doc;
    if (deserializeJson(doc, body)) {
        server.send(400, "application/json", "{\"error\":\"JSON inválido\"}");
        return;
    }
    int    targetId = doc["id"] | 0;
    String newPass  = doc["senha"] | "0000";

    Player* target = findById(targetId);
    if (target) {
        target->senha = auth.hashPin(newPass);
        save();
        server.send(200, "application/json", "{\"success\":true,\"message\":\"Senha do jogador resetada com sucesso!\"}");
    } else {
        server.send(404, "application/json", "{\"error\":\"Jogador não encontrado\"}");
    }
}

void PlayerManager::handleClearPlayers(ESP8266WebServer& server) {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    if (!checkAuthAdmin(server)) return;
    playerCount = 0;
    nextPlayerId = 1;
    save();
    server.send(200, "application/json", "{\"success\":true,\"message\":\"Jogadores limpos\"}");
}
