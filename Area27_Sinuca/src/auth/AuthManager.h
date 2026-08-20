#ifndef AUTH_MANAGER_H
#define AUTH_MANAGER_H

#include <Arduino.h>

struct AuthSession {
    String token;
    int playerId; // -1 for Admin
    unsigned long expiresAt;
    bool active;
};

class AuthManager {
private:
    static const int MAX_SESSIONS = 10;
    static const unsigned long SESSION_DURATION = 3600000UL * 12; // 12 hours
    AuthSession sessions[MAX_SESSIONS];

    String adminHash;
    bool adminConfigured;
    
    // Antifraud / Brute Force
    unsigned long lastFailedAttempt;
    int failedAttempts;

    String generateToken();

public:
    AuthManager();
    void begin(); // Load admin config

    // Hashing
    String hashPin(const String& pin);
    bool verifyPin(const String& pin, const String& storedHash);

    // Admin
    bool isAdminConfigured() const;
    bool configureAdminPin(const String& newPin);
    bool loginAdmin(const String& pin, String& outToken);

    // Players
    bool loginPlayer(int playerId, const String& pin, const String& storedHash, String& outToken);

    // Sessions
    bool validateToken(const String& token, int& outPlayerId);
    void logout(const String& token);
    void cleanupSessions();
    
    // Brute Force protection
    bool isRateLimited();
    void recordFailedAttempt();
    void resetFailedAttempts();
};

extern AuthManager auth;

#endif // AUTH_MANAGER_H
