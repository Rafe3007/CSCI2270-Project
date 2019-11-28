#ifndef FIELD_HPP
#define FIELD_HPP

#include <string>

struct Player {
  bool turn = false;
  string name;
  int hp = 0;
  Deck hand; // POINTER? IF NOT WHAT?

  Player() {} // default
  Player(bool t, string n, int h) : turn(t), name(n), hp(h) {}

  bool isDead() { return if(hp <= 0); } // if this doesn't work, - try removing the if
};

class Field {
  private:
    
  public:
    void buildDeck(const char* deckFile);
}
