#include "NumberGuesser.h"
#include <cstdlib>
#include <ctime>

int NumberGuesser::gamesPlayed = 0;

static bool numberGuesserSeeded = false;

NumberGuesser::NumberGuesser(int lo, int hi)
    : secretNumber(0), maxGuesses(7), guessCount(0), solved(false), low(lo), high(hi) {
    if (!numberGuesserSeeded) {
        srand(static_cast<unsigned int>(time(0)));
        numberGuesserSeeded = true;
    }
    if (low >= high) {
        low = 1;
        high = 100;
    }
    generateSecret();
    gamesPlayed++;
}

NumberGuesser::~NumberGuesser() {
    // no behavior needed
}

void NumberGuesser::setRange(int lo, int hi) {
    if (lo < hi) {
        low = lo;
        high = hi;
        reset();
    }
}

string NumberGuesser::guess(int n) {
    if (solved || guessCount >= maxGuesses) {
        return "Game over.";
    }

    guessCount++;
    if (n == secretNumber) {
        solved = true;
        return "Correct!";
    }
    if (n < secretNumber) {
        return "Too Low";
    }
    return "Too High";
}

void NumberGuesser::reset() {
    generateSecret();
    guessCount = 0;
    solved = false;
    gamesPlayed++;
}

void NumberGuesser::printGamesPlayed() {
    cout << "Number Guesser games played: " << gamesPlayed << endl;
}

void NumberGuesser::generateSecret() {
    secretNumber = rand() % (high - low + 1) + low;
}
