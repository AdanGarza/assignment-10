#ifndef NUMBERGUESSER_H
#define NUMBERGUESSER_H

#include <iostream>
#include <string>
using namespace std;

class NumberGuesser {
public:
    NumberGuesser(int lo = 1, int hi = 100);
    ~NumberGuesser();

    void setRange(int lo, int hi);
    string guess(int n);
    int getGuessCount() const { return guessCount; }
    bool isSolved() const { return solved; }
    void reset();

    static void printGamesPlayed();

private:
    int secretNumber;
    int maxGuesses;
    int guessCount;
    bool solved;
    int low;
    int high;

    static int gamesPlayed;
    void generateSecret();
};

#endif
