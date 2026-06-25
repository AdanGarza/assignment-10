#include "ArcadeManager.h"
#include <cstdlib>
#include <limits>

int ArcadeManager::totalSessions = 0;
ArcadeManager::HighScore ArcadeManager::leaderboard[10] = {};

ArcadeManager::ArcadeManager(const string& player, int tokens)
    : playerName(player), totalTokens(tokens > 0 ? tokens : 100), lastGame("None"),
      sessionWins(0), sessionGamesPlayed(0), slotMachine(totalTokens), guesser(1, 100), scramble() {
    totalSessions++;
    if (tokens <= 0) {
        cout << "Invalid starting tokens; defaulting to 100." << endl;
    }
}

ArcadeManager::~ArcadeManager() {
    cout << "Thanks for visiting the Campus Game Arcade!" << endl;
}

void ArcadeManager::setPlayer(const string& name, int tokens) {
    playerName = name;
    totalTokens = tokens > 0 ? tokens : 100;
    slotMachine.setCoins(totalTokens);
}

void ArcadeManager::launchMenu() {
    int choice;
    do {
        cout << "\n=== CAMPUS ARCADE ===" << endl;
        cout << "1. Slot Machine" << endl;
        cout << "2. Number Guesser" << endl;
        cout << "3. Word Scramble" << endl;
        cout << "4. View Stats" << endl;
        cout << "5. Quit" << endl;
        cout << "Choice: ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 5." << endl;
            continue;
        }
        switch (choice) {
            case 1: runSlots(); break;
            case 2: runGuesser(); break;
            case 3: runScramble(); break;
            case 4: printStats(); break;
            case 5: cout << "Exiting arcade. Goodbye!" << endl; break;
            default: cout << "Please choose a valid option (1-5)." << endl; break;
        }
    } while (choice != 5);
}

void ArcadeManager::printStats() const {
    cout << "\nPlayer: " << playerName << endl;
    cout << "Total tokens: " << totalTokens << endl;
    cout << "Last game: " << lastGame << endl;
    cout << "Session games played: " << sessionGamesPlayed << endl;
    cout << "Session wins: " << sessionWins << endl;
    cout << "Total arcade sessions: " << totalSessions << endl;
}

void ArcadeManager::awardBonus(int amount) {
    if (amount > 0) {
        totalTokens += amount;
        slotMachine.setCoins(totalTokens);
        cout << "Awarded bonus of " << amount << " tokens!" << endl;
    }
}

void ArcadeManager::printLeaderboard() {
    cout << "\n=== ARCADE LEADERBOARD ===" << endl;
    for (int i = 0; i < 10; ++i) {
        if (!leaderboard[i].playerName.empty()) {
            cout << i + 1 << ". " << leaderboard[i].playerName << " - "
                 << leaderboard[i].score << "\n";
        }
    }
}

void ArcadeManager::runSlots() {
    int bet;
    cout << "Enter bet amount: ";
    cin >> bet;
    if (slotMachine.spin(bet)) {
        sessionWins++;
    }
    slotMachine.printResult();
    lastGame = "Slot Machine";
    sessionGamesPlayed++;
}

void ArcadeManager::runGuesser() {
    int guess;
    cout << "Guess a number between 1 and 100: ";
    cin >> guess;
    string result = guesser.guess(guess);
    cout << result << endl;
    if (result == "Correct!") {
        sessionWins++;
    }
    lastGame = "Number Guesser";
    sessionGamesPlayed++;
}

void ArcadeManager::runScramble() {
    cout << "Scrambled word: " << scramble.getScrambled() << endl;
    string attempt;
    cout << "Your guess: ";
    cin >> attempt;
    if (scramble.tryGuess(attempt)) {
        cout << "Correct!" << endl;
        sessionWins++;
    } else {
        cout << "Wrong guess. Lives left: " << scramble.getLivesLeft() << endl;
    }
    cout << "Solution: " << scramble.reveal() << endl;
    lastGame = "Word Scramble";
    sessionGamesPlayed++;
    updateLeaderboard(scramble.getLivesLeft());
}

void ArcadeManager::updateLeaderboard(int score) {
    for (int i = 0; i < 10; ++i) {
        if (leaderboard[i].playerName.empty() || score > leaderboard[i].score) {
            for (int j = 9; j > i; --j) {
                leaderboard[j] = leaderboard[j - 1];
            }
            leaderboard[i].playerName = playerName;
            leaderboard[i].score = score;
            return;
        }
    }
}
