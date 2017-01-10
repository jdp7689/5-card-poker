/*
 * \file CS404_HW8.cpp
 * \date Nov 30, 2016
 * \author Josh Palmer
 */

#include "PokerGame.h"
#include <string>

int main() {
    int numPlayers;
    int numHumanPlayers;
    string input;
    cout << "Welcome to 5 card poker! How many total players "
            << "(human and computer) will be playing (max 7 players, min 2)?" << endl;
    do {
        getline(cin, input);
        numPlayers = atoi(input.c_str());
    } while (numPlayers > 7 || numPlayers < 2);
    cout << "Great! Now, how many human players will be playing?" << endl;
    do {
        getline(cin, input);
        numHumanPlayers = atoi(input.c_str());
    } while (numHumanPlayers > numPlayers);
    PokerGame game(numPlayers, numHumanPlayers);
    game.playGame();

    return 0;
}

