#ifndef FIELD_HPP
#define FIELD_HPP

#include <string>
#include <vector>

using namespace std;

struct Card {
  int health, cost, attack;
  std::string name;
  bool attacked;

  Card() {} // default
  Card(int h, int c, int a, std::string n, bool atk) : health(h), cost(c), attack(a), name(n), attacked(atk) {}
};

struct Player {
  bool turn = false;
  std::string name;
  int hp = 0;
  int mana = 0;
  vector<Card*> hand; 

  Player() {} // default
  Player(bool t, std::string n, int h, int m) : turn(t), name(n), hp(h), mana(m) {}

  bool isDead() { return (hp <= 0); }
  void resetMana(int base) {mana = base;};
};

class Field {
  private:
    vector<Card*> deck;
    Player* p1;
    Player* p2;
    vector<Card*> onFieldTop; // remember to heapSort!
    vector<Card*> onFieldBottom; // remember to heapSort!
    int onField;
    int topField;
    int botField;
    
  public:
    Field();
    void displayField();
    bool checkField(int n);
    int attackPhase(Player* p1, Player* p2);
    bool isTurn(Player p); // Checks if it's player's turn
    void heapSort(vector<Card*> victim);
    void addCreatureTop(Card* creature);
    void addCreatureBot(Card* creature);

    Player* getPlayer1() {return p1;};
    Player* getPlayer2() {return p2;};
    void setPlayer1(Player* p) ;
    void setPlayer2(Player* p) ;
    vector<Card*> getDeck() ;
    void setDeck(vector<Card*> d) ;
    int getTopField() {return topField;};
    int getBotField() {return botField;};

};

#endif