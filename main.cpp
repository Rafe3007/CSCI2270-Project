/*
  -----=[Known Bugs]=------
    - When topField attacks the Bottom hero - It deals damage to both players
    - When botField attacks the Top hero - It does nothing
    - Player health is always displaying the same but somehow keeps track of damage..
      - UPDATE: Tracks the main.cpp player->hp correctly but not the Field_Players
                Affects the display function as well because it's in Field.hpp

     - When players hits enter during turn phase - it registers as '6' (passes turn) [FIXED]
     - Bottom Field doesn't delete Card when it has died [FIXED]
        - UPDATE: It does get deleted, but is delayed a turn
     - Mana system isn't capped at a max [FIXED]

  -----=[Issues]=-----
    - Unbalanced Cards
    - Slightly unfair attack system (topField always attacks first)
      - Ideally would alternate who hits first

*/

#include "Field.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

int convert(string victim) {
  int num;
  stringstream converter(victim);
  converter >> num;
  return num;
}

vector<Card*> buildDeck(const char* deckFile, Field f) {
  ifstream file;
  file.open(deckFile);
  vector<Card*> deck;

  if(!file) {
    std::cout << "ERROR: failed to open file";
  }
  else {
    std::string name, ph;
    int cost, atk, hp;
    bool agro = false;
    while(file.good()) {
      // HEALTH
      getline(file, ph, ',');
      hp = convert(ph);

      // COST
      getline(file, ph, ',');
      cost = convert(ph);

      // DAMAGE
      getline(file, ph, ',');
      atk = convert(ph);

      // NAME
      getline(file, name);

      Card* temp = new Card(hp, cost, atk, name, agro);

      // cout << temp->health << " - " << temp->cost << " - " << temp->attack << " - " << temp->name << " - " << temp->attacked << endl;
      deck.push_back(temp);
    }
    std::cout << "  Deck Initialized.." << endl; // TEST PRINT
  }
  file.close();
  return deck;
}

// vector replace - replaces the current deck in Field
// vector temp - return val
vector<Card*> getCards(vector<Card*> d, int start, int end) { // Grabs 20 cards in deck and creates vector
  vector<Card*> temp;
  for(int i = start; i < end; i++) {
    Card* tmp = d[i];
    temp.push_back(tmp);
  }
  return temp;
}

void readyPrompt(Player* p) {
  // system("CLS");
  string dummy;
  std::cout << "\n [GAME] " << p->name << ", Please hit ENTER to continue";
  getline(cin, dummy);
}

void showHand(Player* p){
  std::cout << " [GAME] "<< p->name << ", Please choose a card to play or press 6 to END your turn\n"<<endl;
  if(p->hand.size() < 5) {
    cout << "Deck is incomplete! Insufficent amount of cards in hand.." << endl;
  } else {
    cout << "--=[Mana: " << p->mana << "]=--\n\n";
    for(int i = 0; i < 5; i++) {
      cout << " " << i+1 << ") " << p->hand[i]->name << "\n    - Mana: " << p->hand[i]->cost << "\n    - HP: " << p->hand[i]->health << "\n    - Attack: " << p->hand[i]->attack << "\n\n";
    }
  }
}

string chooseCard(Player* p){
  string choice;
  getline(cin, choice);
  return choice;
}


int main(int argc, char* argv[]) {
    if(argc < 2) {
    std::cout << "Not enough arguements!";
    return 0;
    } else if(argc > 2) {
        std::cout << "Too many arguemets!";
        return 0;
    }

    const char* dck;
    dck = argv[1];

    std::cout << "\nWelcome to the ARENA!! \n .. You probaly will die here. \nWhat is your name?" << endl;
    
    string strInp;
    getline(cin, strInp);
    Player* p1 = new Player(true, strInp, 20, 3);

    std::cout << "\nChallanger 2! Come forth.. \nWhat is your name?" << endl;
    getline(cin, strInp);
    Player* p2 = new Player(false, strInp, 20, 3);

    std::cout << "\nToday's match we have " << p1->name << " vs. " << p2->name << "!!\n" << endl;
    std::cout << "[loading] Preparing the arena..." << endl;
    // build deck here
    Field field;
    vector<Card*> deck = buildDeck(dck, field);
    field.setDeck(deck);

    // Initialize Player and Deal Cards here
    vector<Card*> p1_hand = getCards(field.getDeck(), 0, (field.getDeck().size() / 2));
    vector<Card*> p2_hand = getCards(field.getDeck(), (field.getDeck().size() / 2), field.getDeck().size());
    p1->hand = p1_hand;
    p2->hand = p2_hand;
    field.setPlayer1(p1);
    field.setPlayer2(p2);
    cout << "  Player One Initialized.." << endl;
    cout << "  Player Two Initialized.." << endl;
    cout << "  Player Hands Initialized.." << endl;

    // Start Game
    //   ENDGAME TESTS:
    //     - If Turns Pass x amount
    //     - If player dies

    bool gameEnd = false;
    int MAX_TURNS = 20;
    int turn = 1;

    // Update player after each round
    while(!gameEnd) {

      //See if it's Player1's Turn
      if(p1->turn){
        readyPrompt(p1);
        field.displayField();

        //Turn Phase
        string choice;
        bool cont = true;
        int num;
        while(cont){
          //1. Show the player their hand
          showHand(p1);
          //2. Have the player choose a card to play
          choice = chooseCard(p1);
          num = convert(choice);
          if(num < 6) {
            if(p1->hand[num-1]->cost > p1->mana) {
              cout << "\n [GAME] !!! You don't have enough mana to play this card! ~ \n\n";
            } else {
              p1->mana -= p1->hand[num-1]->cost;
              field.addCreatureTop(p1->hand[num-1]);
              cout << "\n\n [GAME] ~ " << p1->hand[num-1]->name << " has been played ~ \n\n";
              p1->hand.erase(p1->hand.begin() + num - 1);
            }
          }
          else if(num == 6)
            cont = false;
          else 
            cout << "\n [ERROR] Invalid Argument '" << choice << "'\n\n";
        }

        p1->turn = false;
        p2->turn = true;
      }

      //See if it's Player2's Turn
      if(p2->turn){
        readyPrompt(p2);
        field.displayField();

        //Turn Phase
        string choice;
        
        bool cont = true;
        int num;
        while(cont){
          //1. Show the player their hand
          showHand(p2);
          //2. Have the player choose a card to play
          choice = chooseCard(p2);
          num = convert(choice);
          if(num < 6) {
            if(p2->hand[num-1]->cost > p2->mana) {
              cout << "\n [GAME] !!! You don't have enough mana to play this card!  \n\n";
            } else {
              p2->mana -= p2->hand[num-1]->cost;
              field.addCreatureBot(p2->hand[num-1]);
              cout << "\n\n [GAME] ~ " << p2->hand[num-1]->name << " has been played ~ \n\n";
              p2->hand.erase(p2->hand.begin() + num - 1);
            }
          } 
          else
            cont = false;
        }
        
        p2->turn = false;
        p1->turn = true;
      }

      // Attack Phase
      int count;
      if(field.getTopField() >= field.getBotField())
        count = field.getTopField();
      else if(field.getBotField() >= field.getTopField())
        count = field.getBotField();
      else
        count = 0;

      for(int i = 0; i < count; i++) {
        // field.attackPhase(p1, p2);
        int dmg = field.attackPhase(p1, p2);
        if(dmg != -1) {
          if(field.getTopField() > 0 && field.getBotField() == 0)
            p2->hp -= dmg;
          else if(field.getBotField() > 0 && field.getTopField() == 0)
            p1->hp -= dmg;
        }
      }

      // Add mana points  
      if(turn <= 1) {
        p1->resetMana(3);
        p2->resetMana(3); 
      } else if(turn >= 10){
        p1->resetMana(10);
        p2->resetMana(10);
      } else {
        p1->resetMana(turn + 1);
        p2->resetMana(turn + 1);
      }

      // Tests
      if(p1->isDead()) {
        cout << "=======[GAME OVER]=======" << endl;
        cout << p1->name << " Has Died!\n\n  " << p2->name << "Is Victorious!!" << endl;
        gameEnd = true;
      } else if (p2->isDead()) {
        cout << "=======[GAME OVER]=======" << endl;
        cout << p2->name << " Has Died!\n\n  " << p1->name << "Is Victorious!!" << endl;
        gameEnd = true;
      } else if(turn >= MAX_TURNS) {
        cout << "=======[GAME OVER]=======" << endl;
        cout << " This battle has gone on for too long.. the King was bored has left\n You bring shame to your families" << endl;
        gameEnd = true;
      }

      // cout << "P1 HP: " << field.getPlayer1()->hp << "\nP2 HP: " << field.getPlayer2()->hp << endl;
      // cout << "P1 HP: " << p1->hp << "\nP2 HP: " << p2->hp << endl;
      field.setPlayer1(p1);
      field.setPlayer1(p2);
      turn++;
    }
  return 0;
}