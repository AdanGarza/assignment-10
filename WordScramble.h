#ifndef WORDSCRAMBLE_H
#define WORDSCRAMBLE_H

#include <iostream>
#include <string>
using namespace std;

class WordScramble {
public:
    WordScramble();
    WordScramble(string word, int lives);

    void setWord(const string& word);
    string getScrambled() const { return scrambled; }
    bool tryGuess(const string& attempt);
    int getLivesLeft() const { return livesLeft; }
    string reveal() const;

private:
    string originalWord;
    string scrambled;
    int livesLeft;
    bool won;

    void scramble();
};

#endif