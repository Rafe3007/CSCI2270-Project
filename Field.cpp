#include "field.hpp"
#include "Hash.hpp"
#include <fstream>
#include <sstream>

int convert(string victim) {
  int num;
  stringstream converter(victim);
  converter >> num;
  return num;
}

void Field::buildDeck(const char* deckFile) {
  fstream file;
  file.open(deckFile);

  if(!file)
    cout << "ERROR: failed to open file";

  HashTable(50) deck;
  std::string name, desc, ph;
  int priority, dmg;
  while(!file.eof()) {
    // PRIORITY
    getline(file, ph, ',');
    priority = convert(ph);

    // NAME
    getline(file, name, ',');

    // DESCRIPTION
    getline(file, desc, ',');

    // DAMAGE
    getline(file, ph);
    dmg = convert(ph);

    deck.addCard(priority, name, desc, dmg);
  }
  cout << "Deck successfully created!" << endl; // TEST PRINT
}
