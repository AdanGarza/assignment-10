#include "WordScramble.h"
#include <cstdlib>
#include <ctime>
#include <vector>

static const vector<string> WORD_BANK = {
    "campus", "library", "computer", "arcade", "student",
    "lecture", "project", "semester", "science", "keyboard"
};

static bool wordScrambleSeeded = false;

WordScramble::WordScramble()
    : originalWord(""), scrambled(""), livesLeft(5), won(false) {
    if (!wordScrambleSeeded) {
        srand(static_cast<unsigned int>(time(0)));
        wordScrambleSeeded = true;
    }
    int index = rand() % WORD_BANK.size();
    setWord(WORD_BANK[index]);
}

WordScramble::WordScramble(string word, int lives)
    : originalWord(""), scrambled(""), livesLeft(lives > 0 ? lives : 5), won(false) {
    if (!wordScrambleSeeded) {
        srand(static_cast<unsigned int>(time(0)));
        wordScrambleSeeded = true;
    }
    setWord(word);
}

void WordScramble::setWord(const string& word) {
    originalWord = word;
    scrambled.clear();
    won = false;
    if (livesLeft <= 0) {
        livesLeft = 5;
    }
    scramble();
}

bool WordScramble::tryGuess(const string& attempt) {
    if (won || livesLeft <= 0) {
        return false;
    }
    if (attempt == originalWord) {
        won = true;
        return true;
    }
    livesLeft--;
    return false;
}

string WordScramble::reveal() const {
    if (won || livesLeft <= 0) {
        return originalWord;
    }
    return "[word hidden until the game ends]";
}

void WordScramble::scramble() {
    scrambled = originalWord;
    int n = scrambled.length();
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(scrambled[i], scrambled[j]);
    }
    if (scrambled == originalWord && n > 1) {
        scramble();
    }
}
