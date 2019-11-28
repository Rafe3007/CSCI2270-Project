// #include "Player.hpp"
#include "Hash.hpp"
#include <iostream>
#include <string>

using namespace std;
// P: PLAYER - CURRENT PLAYER'S TURN
void menu(Player p) {

  if(p1.isTurn())
    cout << "+-=====[" << p.getName() << "'s Turn]======-+" << endl;
  else
    cout << "ERROR: Check Turns var";

  cout << "What would you like to do?";
  cout << "\n1) View Deck";
  cout << "\n2) JAzz";
  cout << "\n3) JAzz?";
  cout << "\n3) JAZZ!";
  cout << "\n4) jazz" << endl;

  cout << "+-========================-+" << endl; // possibly take out or make complex :3
}

int main(int argc, char* argv[]) {

  // Player playerOne;
  // Player playerTwo;
  //
  // cout << "Welcome to the game!\nWhat is your name?" << endl;
  // string name, name2;
  // getline(cin, name);
  // playerOne.setName(name);
  // playerOne.toggleTurn();
  //
  // cout << "Oh, I see you have friend! What is their name?" << endl;
  // getline(cin, name);
  // playerTwo.setName(name);
  //
  // menu(playerOne);
  // playerOne.toggleTurn();
  // playerTwo.toggleTurn();
  // menu(playerTwo);

  if(argc < 2) {
    cout << "Not enough arguements!";
    return 0;
  } else if(argc > 2) {
    cout << "Too many arguemets!";
    return 0;
  }

  char* deckFile = "";
  deckFile = argv[2];

  // CREATE DECK AND BATTLEFIELD - TODO
  Field area;
  area.buildDeck(deckFile);

  bool gameEnd = false; // SWITCH IF END OF GAME
  int turnCount = 0; // NUMBER OF TURNS COMPLETED

  while(!gameEnd) {

    /*
    =======================
    =  CARD SELECT PHASE? =
    =======================
      - Show/select cards
      - Input Which cards they want on the Field
        - Limit?
      - Have a Timer?

    */

    /*
    =======================
    =    ATTACK PHASE     =
    =======================
      - Process cards on Field
        - Damage done to players &/or other cards
        - how will it track?
          - bunch of bools?
      - print out end results
    */

    turnCount++;
    // ENDGAME TESTS
    // checks if a player is dead
    if(playerOne.isDead()) {
      cout << playerOne.name << "has been defeated!\nCongrats " << playerTwo.name << "!" << endl;
      gameEnd = true;
    } else if(playerTwo.isDead()) {
      cout << playerTwo.name  << "has been defeated!\nCongrats " << playerOne.name << "!" << endl;
      gameEnd = true;
    }

    // checks if turns have surpassed limit
    if(turnCount > 20) {
      cout << "Its a draw!" << endl;
      gameEnd = true;
    }
  }

  return 0;
}
