#include "ArcadeManager.h"
#include <iostream>
#include <string>

int main() {
    std::string name;
    int tokens;

    std::cout << "Enter your player name: ";
    std::getline(std::cin, name);
    std::cout << "Enter starting tokens: ";
    std::cin >> tokens;

    ArcadeManager arcade(name, tokens);
    arcade.launchMenu();
    cout << "\nFinal leaderboard:" << endl;
    ArcadeManager::printLeaderboard();

    return 0;
}
