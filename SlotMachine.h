#ifndef SLOTMACHINE_H
#define SLOTMACHINE_H

#include <iostream>
#include <string>
using namespace std;

class SlotMachine {
public:
    SlotMachine();                    // default constructor
    SlotMachine(int startCoins);      // param constructor
    ~SlotMachine();                   // destructor

    void setCoins(int c);             // mutator
    bool spin(int bet);               // mutator -- core game logic
    void printResult() const;         // accessor (const!)
    void resetMachine();              // mutator

    // Inline accessor functions -- defined right here in the header
    int getCoins() const { return coins; }
    int getTotalSpins() const { return totalSpins; }

private:
    int coins;
    string reel[3];
    int totalSpins;
    int lastBet;
    int lastPayout;
    string lastOutcome;
    string randomSymbol();  // private helper
};

#endif
