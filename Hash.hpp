#ifndef HASH_HPP
#define HASH_HPP

#include <iostream>

struct Card {
  string name, desc;
  int priority, damage;

  Card(int p, string n, string d, int dmg) : priority(p), name(n), desc(d), damage(dmg) {}
};

class HashTable
{
    int tableSize;  // No. of buckets (linked lists)
    node* *table; // Pointer to an array containing buckets
    node* createNode(int key, node* next);
public:
    HashTable(int bsize);  // Constructor
    bool insertItem(int key); // inserts a key into hash table
    unsigned int hashFunction(int key); // hash function to map values to key
    void printTable();
    node* searchItem(int key);
};

// trying to customize to Card... WIP
class HashTable
{
    int tableSize; // No. of buckets
    Card* createCard(int p, string n, string d, int dmg);
  public:
    HashTAble(int bsize);
    ... addCard(Card nc);
    unsigned int hashFunction(Card nc);
    void printTable();
    Card* searchCard(Card nc);
};

#endif
