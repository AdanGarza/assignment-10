#include "SlotMachine.h"
#include <cstdlib>

static const string SYMBOLS[] = {"Cherry", "Bell", "Bar", "7", "Lemon"};
static const int SYMBOL_COUNT = 5;

SlotMachine::SlotMachine()
    : coins(100), totalSpins(0), lastBet(0), lastPayout(0), lastOutcome("Ready") {
    cout << "=== Welcome to the Campus Slot Machine ===" << endl;
}

SlotMachine::SlotMachine(int startCoins)
    : coins(startCoins > 0 ? startCoins : 100), totalSpins(0), lastBet(0), lastPayout(0), lastOutcome("Ready") {
    if (startCoins <= 0) {
        cout << "Invalid starting coins. Starting with 100 coins instead." << endl;
    }
    cout << "=== Welcome to the Campus Slot Machine ===" << endl;
}

SlotMachine::~SlotMachine() {
    cout << "Thanks for playing! You leave with " << coins << " coins." << endl;
}

void SlotMachine::setCoins(int c) {
    if (c >= 0) {
        coins = c;
    }
}

bool SlotMachine::spin(int bet) {
    if (bet <= 0) {
        cout << "Error: Bet must be greater than zero." << endl;
        return false;
    }
    if (bet > coins) {
        cout << "Error: You do not have enough coins to make that bet." << endl;
        return false;
    }

    for (int i = 0; i < 3; ++i) {
        reel[i] = randomSymbol();
    }

    int matchCount = 1;
    if (reel[0] == reel[1]) matchCount++;
    if (reel[0] == reel[2]) matchCount++;
    if (reel[1] == reel[2] && reel[0] != reel[1]) matchCount++;

    if (matchCount == 3) {
        lastPayout = bet * 5;
        coins += lastPayout;
        lastOutcome = "Jackpot! Three matching symbols!";
    } else if (matchCount == 2) {
        lastPayout = bet * 2;
        coins += lastPayout;
        lastOutcome = "Nice! Two matching symbols!";
    } else {
        lastPayout = -bet;
        coins -= bet;
        lastOutcome = "No match, you lose the bet.";
    }

    totalSpins++;
    return (matchCount >= 2);
}

void SlotMachine::printResult() const {
    cout << "Reels: [ " << reel[0] << " | " << reel[1] << " | " << reel[2] << " ]" << endl;
    cout << lastOutcome << endl;
    if (lastPayout >= 0) {
        cout << "Payout: " << lastPayout << " coins." << endl;
    } else {
        cout << "Loss: " << -lastPayout << " coins." << endl;
    }
    cout << "Current coins: " << coins << endl;
}

void SlotMachine::resetMachine() {
    coins = 100;
    totalSpins = 0;
    lastBet = 0;
    lastPayout = 0;
    lastOutcome = "Machine reset.";
}

string SlotMachine::randomSymbol() {
    int index = rand() % SYMBOL_COUNT;
    return SYMBOLS[index];
}
