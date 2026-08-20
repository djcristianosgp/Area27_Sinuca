#include "AuthManager.h"
#include <Hash.h>
#include <LittleFS.h>

AuthManager auth;

AuthManager::AuthManager() {
    adminConfigured = false;
    lastFailedAttempt = 0;
    failedAttempts = 0;
    for (int i = 0; i < MAX_SESSIONS; i++) {
        sessions[i].active = false;
    }
}

void AuthManager::begin() {
    if (LittleFS.exists("/admin.hash")) {
        File file = LittleFS.open("/admin.hash", "r");
        if (file) {
            adminHash = file.readStringUntil('\n');
            adminHash.trim();
            file.close();
            if (adminHash.length() > 0) {
                adminConfigured = true;
            }
        }
    }
}

String AuthManager::hashPin(const String& pin) {
    // Simple SHA1 hash of the PIN + a fixed salt for Area27
    String salt = "Area27_Salt_";
    return sha1(salt + pin);
}

bool AuthManager::verifyPin(const String& pin, const String& storedHash) {
    if (storedHash.length() == 0) return false;
    // For backwards compatibility during migration phase, if storedHash is length 4, it's plaintext
    if (storedHash.length() == 4) {
        return storedHash == pin;
    }
    return hashPin(pin) == storedHash;
}

bool AuthManager::isAdminConfigured() const {
    return adminConfigured;
}

bool AuthManager::configureAdminPin(const String& newPin) {
    if (newPin.length() < 4) return false;
    adminHash = hashPin(newPin);
    
    File file = LittleFS.open("/admin.hash", "w");
    if (!file) return false;
    file.print(adminHash + "\n");
    file.close();
    
    adminConfigured = true;
    return true;
}

String AuthManager::generateToken() {
    const char chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    String token = "";
    for (int i = 0; i < 32; i++) {
        token += chars[random(0, sizeof(chars) - 1)];
    }
    return token;
}

bool AuthManager::isRateLimited() {
    if (failedAttempts >= 5) {
        unsigned long cooldown = 30000; // 30s block
        if (millis() - lastFailedAttempt < cooldown) {
            return true;
        } else {
            resetFailedAttempts();
        }
    } else if (failedAttempts > 0) {
        // Progressive delay: 1s, 2s, 3s...
        unsigned long delayTime = failedAttempts * 1000;
        if (millis() - lastFailedAttempt < delayTime) {
            return true;
        }
    }
    return false;
}

void AuthManager::recordFailedAttempt() {
    failedAttempts++;
    lastFailedAttempt = millis();
}

void AuthManager::resetFailedAttempts() {
    failedAttempts = 0;
    lastFailedAttempt = 0;
}

bool AuthManager::loginAdmin(const String& pin, String& outToken) {
    cleanupSessions();
    if (isRateLimited()) return false;

    if (!adminConfigured) {
        // Fallback default admin if not configured (should trigger configuration flow in frontend)
        if (pin == "0000") {
            resetFailedAttempts();
            outToken = generateToken();
            // Find empty session
            for (int i = 0; i < MAX_SESSIONS; i++) {
                if (!sessions[i].active) {
                    sessions[i] = {outToken, -1, millis() + SESSION_DURATION, true};
                    return true;
                }
            }
        }
        recordFailedAttempt();
        return false;
    }

    if (verifyPin(pin, adminHash)) {
        resetFailedAttempts();
        outToken = generateToken();
        for (int i = 0; i < MAX_SESSIONS; i++) {
            if (!sessions[i].active) {
                sessions[i] = {outToken, -1, millis() + SESSION_DURATION, true};
                return true;
            }
        }
    }
    
    recordFailedAttempt();
    return false;
}

bool AuthManager::loginPlayer(int playerId, const String& pin, const String& storedHash, String& outToken) {
    cleanupSessions();
    if (isRateLimited()) return false;

    if (verifyPin(pin, storedHash)) {
        resetFailedAttempts();
        outToken = generateToken();
        // Evict old session for this player if exists
        for (int i = 0; i < MAX_SESSIONS; i++) {
            if (sessions[i].active && sessions[i].playerId == playerId) {
                sessions[i].active = false;
            }
        }
        for (int i = 0; i < MAX_SESSIONS; i++) {
            if (!sessions[i].active) {
                sessions[i] = {outToken, playerId, millis() + SESSION_DURATION, true};
                return true;
            }
        }
    }
    
    recordFailedAttempt();
    return false;
}

bool AuthManager::validateToken(const String& token, int& outPlayerId) {
    cleanupSessions();
    for (int i = 0; i < MAX_SESSIONS; i++) {
        if (sessions[i].active && sessions[i].token == token) {
            outPlayerId = sessions[i].playerId;
            return true;
        }
    }
    return false;
}

void AuthManager::logout(const String& token) {
    for (int i = 0; i < MAX_SESSIONS; i++) {
        if (sessions[i].active && sessions[i].token == token) {
            sessions[i].active = false;
            break;
        }
    }
}

void AuthManager::cleanupSessions() {
    unsigned long now = millis();
    for (int i = 0; i < MAX_SESSIONS; i++) {
        if (sessions[i].active && (now > sessions[i].expiresAt)) {
            sessions[i].active = false;
        }
    }
}
