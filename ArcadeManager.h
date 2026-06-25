#ifndef ARCADEMANAGER_H
#define ARCADEMANAGER_H

#include <iostream>
#include <string>
#include "SlotMachine.h"
#include "NumberGuesser.h"
#include "WordScramble.h"
using namespace std;

class ArcadeManager {
public:
    struct HighScore {
        string playerName;
        int score;
    };

    ArcadeManager(const string& player, int tokens);
    ~ArcadeManager();

    void setPlayer(const string& name, int tokens);
    void launchMenu();
    void printStats() const;
    void awardBonus(int amount);

    static void printLeaderboard();

private:
    string playerName;
    int totalTokens;
    string lastGame;
    int sessionWins;
    int sessionGamesPlayed;
    SlotMachine slotMachine;
    NumberGuesser guesser;
    WordScramble scramble;

    static int totalSessions;
    static HighScore leaderboard[10];

    void runSlots();
    void runGuesser();
    void runScramble();
    void updateLeaderboard(int score);
};

#endif
