#ifndef TYPES_H
#define TYPES_H

#include <Arduino.h>

struct Player {
  int id;
  String nome;
  String telefone;
  String senha;
  int elo;
  int vitorias;
  int derrotas;
  int peak_elo;
  int max_win_streak;
  int current_streak;
  int titles_count;
  int shutout_count;
};

struct ActiveMatch {
  bool active;
  String code;
  String matchType;
  int maxPlayers;
  int playerIds[4];
  String invites[4];
  String status;
  int winner_id;
  int loser_balls;
  unsigned long startMillis;
};

struct MatchHistoryItem {
  int id;
  String matchType;
  int p1_id;
  int p2_id;
  int winner_id;
  int loser_balls;
  int elo_delta;
  String date_str;
};

struct SeasonRecord {
  int id;
  String name;
  String champion;
  String vice;
  String third;
};

#endif // TYPES_H
