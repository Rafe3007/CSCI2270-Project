#include "Field.hpp"
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

Field::Field() {
    onField = 0;
    topField = 0;
    botField = 0;
    cout << "  Field Initialized.." << endl;
}

void Field::setDeck(vector<Card*> d) {
    deck = d;
}

void Field::setPlayer1(Player* p) {
    p1 = p;
    // cout << "  Player One Initialized.." << endl;
}

void Field::setPlayer2(Player* p) {
    p2 = p;
    // cout << "  Player Two Initialized.." << endl;
}

vector<Card*> Field::getDeck() {
    if(deck.size() == 0) 
        cout << "Deck is empty!" << endl;
    return deck;
}

bool heapHelper(const Card* first, const Card* second) {
    return first->attack > second->attack;
}

void Field::heapSort(vector<Card*> victim) {
    make_heap(victim.begin(), victim.end(), heapHelper);
}

void Field::addCreatureTop(Card* creature) {
    onFieldTop.push_back(creature);
    push_heap(onFieldTop.begin(), onFieldTop.end(), heapHelper);
    heapSort(onFieldTop);
    topField++;
    onField++;
}

void Field::addCreatureBot(Card* creature) {
    onFieldBottom.push_back(creature);
    push_heap(onFieldBottom.begin(), onFieldBottom.end(), heapHelper);
    heapSort(onFieldBottom);
    botField++;
    onField++;
}

/* Cases:
    1 - Nothing on Field
    2 - Cards on both Fields
    3 - Cards on top Field only
    4 - Cards on bottom Field only
*/
int Field::attackPhase(Player* p1, Player* p2){
    // Case: 1
    if(onField <= 0)
        return -1;
    // else if(p->turn){ //player 1's attack phase on the bottom field
    //   //1. Only player one has a creature on the field, so attack the hero
    //   if((onFieldTop.size()>=1) && (onFieldBottom.size() == 0)){
    //     p2->hp -= onFieldTop[0]->attack;
    //   }
    //   //2. Both players have creatures on the field, so find the two lowest attack ceratures on the field
    //     //and have p1's attack p12's
    //   if((onFieldTop.size()>=1)&&(onFieldBottom.size()>=1)){
    //     onFieldBottom[0]->health -= onFieldTop[0]->attack;
    //     onFieldTop[0]->health -= onFieldBottom[0]->attack;
    //     if(onFieldBottom[0]->health <= 0)
    //       onFieldBottom.pop_back();
    //     if(onFieldTop[0]->health <= 0)
    //       onFieldTop.pop_back();
    //   }
    // }
    // else if(p->turn){//player 2's attack phase on the top field
    //   //1. Only player two has a creature on the field, so attack the hero
    //   if((onFieldBottom.size() >=1) && (onFieldTop.size() == 0)){
    //     p1->hp -= onFieldBottom[0]->attack;
    //   }
    //   //2. Both players have creatures on the field, so find the two lowest attack ceratures on the field
    //     //and have pl2's attack pl1's
    //    if((onFieldBottom.size()>=1)&&(onFieldTop.size() >= 1)){
    //     onFieldTop[0]->health -= onFieldBottom[0]->attack;
    //     onFieldBottom[0]->health -= onFieldTop[0]->attack;
    //     if(onFieldBottom[0]->health <= 0)
    //       onFieldBottom.pop_back();
    //     if(onFieldTop[0]->health <= 0)
    //       onFieldTop.pop_back();
    //     }
    //   }

    // Case: 2
    else if(topField > 0 && botField > 0) {
        // cout << "-==--=-= Case: 2 =-=-=-=-\n\n";
        Card* top_temp = onFieldTop[0];
        Card* bot_temp = onFieldBottom[0];
        if(p1->turn) {
            bot_temp->health -= top_temp->attack;

            // Checks if bottom card has been killed (defense)
            if(bot_temp->health > 0) {
                top_temp->health -= bot_temp->attack;
                onFieldBottom[0] = bot_temp;
            } else { // Remove Card from Bottom Field
                onFieldBottom.erase(onFieldBottom.begin());
                botField--;
                onField--;
            }

            // Checks if top card has been killed - Remove from Top Field
            if(top_temp->health <= 0) {
                onFieldTop.erase(onFieldTop.begin());
                topField--;
                onField--;
            }
            else
                onFieldTop[0] = top_temp;
        } else {
            top_temp->health -= bot_temp->attack;

            // Checks if top card has been killed (defense)
            if(top_temp->health > 0) {
                bot_temp->health -= top_temp->attack;
                onFieldTop[0] = top_temp;
            } else { // Remove Card from Top Field
                onFieldTop.erase(onFieldTop.begin());
                topField--;
                onField--;
            }

            // Checks if bottom card has been killed - Remove from Bottom Field
            if(bot_temp->health <= 0) {
                onFieldBottom.erase(onFieldBottom.begin());
                botField--;
                onField--;
            }
            else
                onFieldBottom[0] = bot_temp;
        }
    }

    // Case: 3
    else if(topField > 0 && botField == 0) {
        // cout << "-==--=-= Case: 3 =-=-=-=-\n\n";
        // p1->hp -= onFieldTop[0]->attack;
        return onFieldTop[0]->attack;
    }

    // Case: 4
    else if(botField > 0 && topField == 0) {
        // cout << "-==--=-= Case: 4 =-=-=-=-\n\n";
        // p2->hp -= onFieldBottom[0]->attack;
        return onFieldBottom[0]->attack;
    }
    return -1;
}

void displayFieldHelper(vector<Card*> cards) {
    int count = cards.size();
    if(count <= 3) {
        for(int i = 0; i < count; i++) {
            cout << "   | " << cards[i]->name << " |   ";
        }
        cout << endl;
        for(int i = 0; i < count; i++) {
            cout << "  A:" << cards[i]->attack;
            for(int j = 0; j < cards[i]->name.length(); j++) {
                cout << " ";
            }
            cout << "H:" << cards[i]->health << "  ";
        }
    }
    else if(count > 3 && count <= 6) {
        for(int i = 0; i < 3; i++) {
            cout << "   | " << cards[i]->name << " |   ";
        }
        cout << endl;
        for(int i = 0; i < 3; i++) {
            cout << "  A:" << cards[i]->attack;
            for(int j = 0; j < cards[i]->name.length(); j++) {
                cout << " ";
            }
            cout << "H:" << cards[i]->health << "  ";
        }
        cout << "\n\n";
        for(int i = 3; i < count; i++) {
            cout << "   | " << cards[i]->name << " |   ";
        }
        cout << endl;
        for(int i = 3; i < count; i++) {
            cout << "  A:" << cards[i]->attack;
            for(int j = 0; j < cards[i]->name.length(); j++) {
                cout << " ";
            }
            cout << "H:" << cards[i]->health << "  ";
        }
    }
    else if(count > 6 && count <= 9) {
        for(int i = 0; i < 3; i++) {
            cout << "   | " << cards[i]->name << " |   ";
        }
        cout << endl;
        for(int i = 0; i < 3; i++) {
            cout << "  A:" << cards[i]->attack;
            for(int j = 0; j < cards[i]->name.length(); j++) {
                cout << " ";
            }
            cout << "H:" << cards[i]->health << "  ";
        }
        cout << "\n\n";
        for(int i = 3; i < count; i++) {
            cout << "   | " << cards[i]->name << " |   ";
        }
        cout << endl;
        for(int i = 3; i < count; i++) {
            cout << "  A:" << cards[i]->attack;
            for(int j = 0; j < cards[i]->name.length(); j++) {
                cout << " ";
            }
            cout << "H:" << cards[i]->health << "  ";
        }
        cout << "\n\n";
        for(int i = 6; i < count; i++) {
            cout << "   | " << cards[i]->name << " |   ";
        }
        cout << endl;
        for(int i = 6; i < count; i++) {
            cout << "  A:" << cards[i]->attack;
            for(int j = 0; j < cards[i]->name.length(); j++) {
                cout << " ";
            }
            cout << "H:" << cards[i]->health << "  ";
        }
    }
    else
        cout << "Too many Cards!" << endl;
}

void Field::displayField() {
    // system("CLS");
    cout << "=-~-=-~-=-~-=-~-=-~-=-~-=[ " << p1->hp << " ]~-=-~-=-~-=-~-=-~-=-~-=-~-=\n" << endl;
    displayFieldHelper(onFieldTop);
    cout << "\n ________________________________________________________\n\n";
    displayFieldHelper(onFieldBottom);
    cout << "\n\n=-~-=-~-=-~-=-~-=-~-=-~-=[ " << p2->hp << " ]~-=-~-=-~-=-~-=-~-=-~-=-~-=\n" << endl;
}