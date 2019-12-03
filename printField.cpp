#include <iostream>
#include <string>
#include <vector>

using namespace std;

void printThing(vector<string> name, vector<int> attack, vector<int> health) {
    int count = name.size();
    if(count <= 3) {
        for(int i = 0; i < count; i++) {
            cout << "   | " << name[i] << " |    "; 
        }
        cout << endl;
        for(int i = 0; i < count; i++) {
            cout << "  A:" << attack[i];
            for(int j = 0; j < name[i].length(); j++) {
                cout << " ";
            }
            cout << "H:" << health[i] << "  ";
        }
    } 
    else if(count > 3 && count <= 6) {
        for(int i = 0; i < 3; i++) {
            cout << "   | " << name[i] << " |    "; 
        }
        cout << endl;
        for(int i = 0; i < 3; i++) {
            cout << "  A:" << attack[i];
            for(int j = 0; j < name[i].length(); j++) {
                cout << " ";
            }
            cout << "H:" << health[i] << "  ";
        }
        cout << "\n\n";
        for(int i = 3; i < count; i++) {
            cout << "   | " << name[i] << " |    "; 
        }
        cout << endl;
        for(int i = 3; i < count; i++) {
            cout << "  A:" << attack[i];
            for(int j = 0; j < name[i].length(); j++) {
                cout << " ";
            }
            cout << "H:" << health[i] << "  ";
        }
    }
    else if(count > 6 && count <= 9) {
        for(int i = 0; i < 3; i++) {
            cout << "   | " << name[i] << " |    "; 
        }
        cout << endl;
        for(int i = 0; i < 3; i++) {
            cout << "  A:" << attack[i];
            for(int j = 0; j < name[i].length(); j++) {
                cout << " ";
            }
            cout << "H:" << health[i] << "  ";
        }
        cout << "\n\n";
        for(int i = 3; i < 6; i++) {
            cout << "   | " << name[i] << " |    "; 
        }
        cout << endl;
        for(int i = 3; i < 6; i++) {
            cout << "  A:" << attack[i];
            for(int j = 0; j < name[i].length(); j++) {
                cout << " ";
            }
            cout << "H:" << health[i] << "  ";
        }
        cout << "\n\n";
        for(int i = 6; i < count; i++) {
            cout << "   | " << name[i] << " |    "; 
        }
        cout << endl;
        for(int i = 6; i < count; i++) {
            cout << "  A:" << attack[i];
            for(int j = 0; j < name[i].length(); j++) {
                cout << " ";
            }
            cout << "H:" << health[i] << "  ";
        }
    }
    else 
        cout << "Too many Cards!" << endl;
}

int main() {
    // Test print

    cout << "\n=-~-=-~-=-~-=-~-=-~-=-~-=-~-=-~-=-~-=-~-=-~-=-~-=-~-=\n" << endl;

    vector<string> name = {"Pudson", "Jeff", "Hipley", "John", "Some Long Name", "Renee", "Hopper", "mo", "k"};
    vector<int> attack = {3,1,8,5,1,3,7,2,13};
    vector<int> health = {20,15,20,10,15,8,14,30,13};

    printThing(name, attack, health);
    
    cout << "\n __________________________________________________";
    cout << "\n\n";

    vector<string> name2 = {"Johhny", "Emmett", "Ramon", "Lucy"};
    vector<int> attack2 = {5,2,6,9};
    vector<int> health2 = {15,20,15,20};

    printThing(name2, attack2, health2);

    cout << "\n\n=-~-=-~-=-~-=-~-=-~-=-~-=-~-=-~-=-~-=-~-=-~-=-~-=-~-=\n" << endl;
} 
