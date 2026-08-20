#include "MatchManager.h"
#include <ArduinoJson.h>

MatchManager matchMgr;

MatchManager::MatchManager() {
    activeMatch = {false, "", "par_impar_2p", 2, {0,0,0,0}, {"empty","empty","empty","empty"}, "none", 0, 0, 0};
}

void MatchManager::begin() {
    load();
}

void MatchManager::save() {
    storage.saveHistory(matchHistory, matchHistoryCount);
}

void MatchManager::load() {
    storage.loadHistory(matchHistory, matchHistoryCount);
}

String MatchManager::generateMatchCode() {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    String code = "";
    for (int i = 0; i < 5; i++) {
        code += charset[random(0, 36)];
    }
    return code;
}

String MatchManager::getHistoryJSON() {
    String json = "[\n";
    for (int i = 0; i < matchHistoryCount; i++) {
        Player* p1 = nullptr;
        Player* p2 = nullptr;
        Player* win = nullptr;
        for (int k = 0; k < playerMgr.playerCount; k++) {
            if (playerMgr.players[k].id == matchHistory[i].p1_id) p1 = &playerMgr.players[k];
            if (playerMgr.players[k].id == matchHistory[i].p2_id) p2 = &playerMgr.players[k];
            if (playerMgr.players[k].id == matchHistory[i].winner_id) win = &playerMgr.players[k];
        }

        json += "  {\n";
        json += "    \"id\":" + String(matchHistory[i].id) + ",\n";
        json += "    \"matchType\":\"" + matchHistory[i].matchType + "\",\n";
        json += "    \"p1_nome\":\"" + (p1 ? p1->nome : "Desconhecido") + "\",\n";
        json += "    \"p2_nome\":\"" + (p2 ? p2->nome : "Desconhecido") + "\",\n";
        json += "    \"winner_nome\":\"" + (win ? win->nome : "Desconhecido") + "\",\n";
        json += "    \"loser_balls\":" + String(matchHistory[i].loser_balls) + ",\n";
        json += "    \"elo_delta\":" + String(matchHistory[i].elo_delta) + ",\n";
        json += "    \"date_str\":\"" + matchHistory[i].date_str + "\"\n";
        json += "  }";
        if (i < matchHistoryCount - 1) json += ",";
        json += "\n";
    }
    json += "]";
    return json;
}

void MatchManager::updateMatchStatus() {
    if (!activeMatch.active) return;
    int acceptedCount = 0;
    for (int i = 0; i < activeMatch.maxPlayers; i++) {
        if (activeMatch.playerIds[i] > 0 && (activeMatch.invites[i] == "creator" || activeMatch.invites[i] == "accepted")) {
            acceptedCount++;
        }
    }
    if (acceptedCount >= activeMatch.maxPlayers) {
        activeMatch.status = "in_progress";
    } else {
        activeMatch.status = "waiting";
    }
}

void MatchManager::handleCreateMatch(ESP8266WebServer& server) {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    if (!checkAuthAny(server)) return;
    if (!server.hasArg("plain")) return;
    String body = server.arg("plain");

    String type = "par_impar_2p";
    int typePos = body.indexOf("\"matchType\":\"");
    if (typePos != -1) {
        int tStart = body.indexOf("\"", typePos + 11) + 1;
        int tEnd   = body.indexOf("\"", tStart);
        type       = body.substring(tStart, tEnd);
    }

    int creatorId = 0;
    int pAPos = body.indexOf("\"playerA\":");
    if (pAPos == -1) pAPos = body.indexOf("\"creator\":");
    if (pAPos != -1) {
        int colonPos = body.indexOf(":", pAPos);
        creatorId = body.substring(colonPos + 1).toInt();
    }

    int playerBId = 0;
    int pBPos = body.indexOf("\"playerB\":");
    if (pBPos == -1) pBPos = body.indexOf("\"opponent\":");
    if (pBPos != -1) {
        int colonPos = body.indexOf(":", pBPos);
        playerBId = body.substring(colonPos + 1).toInt();
    }

    int maxP = (type == "par_impar_4p") ? 4 : ((type == "5_bolas_3p") ? 3 : 2);
    String code = generateMatchCode();

    activeMatch.active = true;
    activeMatch.code = code;
    activeMatch.matchType = type;
    activeMatch.maxPlayers = maxP;
    activeMatch.winner_id = 0;
    activeMatch.loser_balls = 0;
    activeMatch.startMillis = millis();

    for (int i = 0; i < 4; i++) {
        activeMatch.playerIds[i] = 0;
        activeMatch.invites[i] = "empty";
    }

    activeMatch.playerIds[0] = creatorId;
    activeMatch.invites[0] = "creator";

    if (playerBId > 0 && playerBId != creatorId) {
        activeMatch.playerIds[1] = playerBId;
        activeMatch.invites[1] = "pending";
    }

    updateMatchStatus();

    server.send(200, "application/json", "{\"success\":true,\"code\":\"" + code + "\",\"matchType\":\"" + type + "\",\"status\":\"" + activeMatch.status + "\"}");
}

void MatchManager::handleJoinMatch(ESP8266WebServer& server) {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    if (!checkAuthAny(server)) return;
    if (!server.hasArg("plain")) return;
    String body = server.arg("plain");

    String code = "";
    int codePos = body.indexOf("\"code\":\"");
    if (codePos != -1) {
        int cStart = body.indexOf("\"", codePos + 7) + 1;
        int cEnd   = body.indexOf("\"", cStart);
        code       = body.substring(cStart, cEnd);
    }
    code.toUpperCase();

    int pId = 0;
    int pPos = body.indexOf("\"playerId\":");
    if (pPos != -1) {
        int colonPos = body.indexOf(":", pPos);
        pId = body.substring(colonPos + 1).toInt();
    }

    if (!activeMatch.active || activeMatch.code != code) {
        server.send(404, "application/json", "{\"error\":\"Sala não encontrada ou inativa\"}");
        return;
    }

    bool alreadyIn = false;
    for (int i = 0; i < activeMatch.maxPlayers; i++) {
        if (activeMatch.playerIds[i] == pId) {
            alreadyIn = true;
            activeMatch.invites[i] = "accepted";
            break;
        }
    }

    if (alreadyIn) {
        updateMatchStatus();
        server.send(200, "application/json", "{\"success\":true,\"message\":\"Retornou à sala\"}");
        return;
    }

    int freeSlot = -1;
    for (int i = 0; i < activeMatch.maxPlayers; i++) {
        if (activeMatch.playerIds[i] == 0) { freeSlot = i; break; }
    }

    if (freeSlot != -1) {
        activeMatch.playerIds[freeSlot] = pId;
        activeMatch.invites[freeSlot] = "accepted";
        updateMatchStatus();
        server.send(200, "application/json", "{\"success\":true,\"message\":\"Entrou na sala\"}");
    } else {
        server.send(400, "application/json", "{\"error\":\"Sala cheia\"}");
    }
}

void MatchManager::handleRespondInvite(ESP8266WebServer& server) {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    if (!checkAuthAny(server)) return;
    if (!server.hasArg("plain")) return;
    String body = server.arg("plain");

    int pId = 0;
    int pPos = body.indexOf("\"playerId\":");
    if (pPos != -1) {
        int colonPos = body.indexOf(":", pPos);
        pId = body.substring(colonPos + 1).toInt();
    }

    String action = "accept";
    int actPos = body.indexOf("\"action\":\"");
    if (actPos != -1) {
        int aStart = body.indexOf("\"", actPos + 9) + 1;
        int aEnd   = body.indexOf("\"", aStart);
        action     = body.substring(aStart, aEnd);
    }

    if (!activeMatch.active) {
        server.send(404, "application/json", "{\"error\":\"Nenhuma partida ativa\"}");
        return;
    }

    bool found = false;
    for (int i = 0; i < activeMatch.maxPlayers; i++) {
        if (activeMatch.playerIds[i] == pId) {
            found = true;
            if (action == "accept") {
                activeMatch.invites[i] = "accepted";
            } else if (action == "reject") {
                activeMatch.playerIds[i] = 0;
                activeMatch.invites[i] = "empty";
            }
            break;
        }
    }

    if (found) {
        updateMatchStatus();
        server.send(200, "application/json", "{\"success\":true,\"message\":\"Resposta registrada\"}");
    } else {
        server.send(404, "application/json", "{\"error\":\"Jogador não está no convite\"}");
    }
}

void MatchManager::handleGetActiveMatch(ESP8266WebServer& server) {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    String json = "{\n";
    json += "  \"active\": " + String(activeMatch.active ? "true" : "false") + ",\n";
    json += "  \"code\": \"" + activeMatch.code + "\",\n";
    json += "  \"matchType\": \"" + activeMatch.matchType + "\",\n";
    json += "  \"maxPlayers\": " + String(activeMatch.maxPlayers) + ",\n";
    json += "  \"status\": \"" + activeMatch.status + "\",\n";
    json += "  \"winner\": " + String(activeMatch.winner_id) + ",\n";
    json += "  \"loser_balls\": " + String(activeMatch.loser_balls) + ",\n";
    json += "  \"players\": [\n";

    for (int i = 0; i < activeMatch.maxPlayers; i++) {
        int pId = activeMatch.playerIds[i];
        Player* pObj = nullptr;
        if (pId > 0) {
            for (int k = 0; k < playerMgr.playerCount; k++) {
                if (playerMgr.players[k].id == pId) { pObj = &playerMgr.players[k]; break; }
            }
        }

        json += "    {\n";
        json += "      \"slot\": " + String(i) + ",\n";
        json += "      \"id\": " + String(pId) + ",\n";
        json += "      \"nome\": \"" + (pObj ? pObj->nome : "Vaga Livre") + "\",\n";
        json += "      \"elo\": " + String(pObj ? pObj->elo : 1000) + ",\n";
        json += "      \"invite\": \"" + activeMatch.invites[i] + "\"\n";
        json += "    }";
        if (i < activeMatch.maxPlayers - 1) json += ",";
        json += "\n";
    }
    json += "  ]\n";
    json += "}";
    server.send(200, "application/json", json);
}

void MatchManager::handleFinishMatch(ESP8266WebServer& server) {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    if (!checkAuthAny(server)) return;
    if (!server.hasArg("plain")) return;

    String body = server.arg("plain");
    int winPos = body.indexOf("\"winner_id\":");
    if (winPos == -1) winPos = body.indexOf("\"winner\":");
    if (winPos == -1) { server.send(400, "application/json", "{\"error\":\"Vencedor ausente\"}"); return; }
    int colonPos = body.indexOf(":", winPos);
    int winVal = body.substring(colonPos + 1).toInt();

    int loserBalls = 0;
    int ballsPos = body.indexOf("\"loserBalls\":");
    if (ballsPos == -1) ballsPos = body.indexOf("\"loser_balls\":");
    if (ballsPos != -1) {
        int bColon = body.indexOf(":", ballsPos);
        loserBalls = body.substring(bColon + 1).toInt();
    }

    int p1_id = activeMatch.playerIds[0];
    int p2_id = activeMatch.playerIds[1];

    Player* pA = nullptr;
    Player* pB = nullptr;
    for (int i = 0; i < playerMgr.playerCount; i++) {
        if (playerMgr.players[i].id == p1_id) pA = &playerMgr.players[i];
        if (playerMgr.players[i].id == p2_id) pB = &playerMgr.players[i];
    }

    int eloDelta = 18;
    if (pA && pB) {
        float expectedA = 1.0 / (1.0 + pow(10.0, (pB->elo - pA->elo) / 400.0));
        float scoreA = (winVal == p1_id) ? 1.0 : 0.0;
        eloDelta = (int)(32 * (scoreA - expectedA));

        if (winVal == p1_id) {
            pA->vitorias++; pA->current_streak++;
            if (pA->current_streak > pA->max_win_streak) pA->max_win_streak = pA->current_streak;
            pA->elo += abs(eloDelta);
            if (pA->elo > pA->peak_elo) pA->peak_elo = pA->elo;
            if (loserBalls == 0) pA->shutout_count++;

            pB->derrotas++; pB->current_streak = 0;
            pB->elo = max(100, pB->elo - abs(eloDelta));
        } else {
            pB->vitorias++; pB->current_streak++;
            if (pB->current_streak > pB->max_win_streak) pB->max_win_streak = pB->current_streak;
            pB->elo += abs(eloDelta);
            if (pB->elo > pB->peak_elo) pB->peak_elo = pB->elo;
            if (loserBalls == 0) pB->shutout_count++;

            pA->derrotas++; pA->current_streak = 0;
            pA->elo = max(100, pA->elo - abs(eloDelta));
        }
    }

    playerMgr.save();

    if (matchHistoryCount < MAX_HISTORY) {
        matchHistory[matchHistoryCount] = { matchHistoryCount + 1, activeMatch.matchType, p1_id, p2_id, winVal, loserBalls, abs(eloDelta), "Hoje" };
        matchHistoryCount++;
        save();
    }

    activeMatch.active = false;
    activeMatch.status = "finished";
    activeMatch.winner_id = winVal;
    activeMatch.loser_balls = loserBalls;

    server.send(200, "application/json", "{\"success\":true,\"message\":\"Partida registrada!\"}");
}

void MatchManager::handleCancelMatch(ESP8266WebServer& server) {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    if (!checkAuthAny(server)) return;
    activeMatch = {false, "", "par_impar_2p", 2, {0,0,0,0}, {"empty","empty","empty","empty"}, "none", 0, 0, 0};
    server.send(200, "application/json", "{\"success\":true,\"message\":\"Partida cancelada\"}");
}

void MatchManager::loop() {
    if (activeMatch.active && activeMatch.status == "waiting") {
        if (millis() - activeMatch.startMillis >= 1800000UL) {
            activeMatch = {false, "", "par_impar_2p", 2, {0,0,0,0}, {"empty","empty","empty","empty"}, "none", 0, 0, 0};
            Serial.println("[MATCH] Partida cancelada automaticamente por tempo limite de 30 minutos sem iniciar.");
        }
    }
}
