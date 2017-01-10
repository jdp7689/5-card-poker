/*
 * \file PokerGame.h
 * \date Nov 15, 2016
 * \author Josh Palmer
 */

#ifndef POKERGAME_H_
#define POKERGAME_H_

#include <vector>
#include <ctype.h>
#include <algorithm>
#include <iostream>
#include <memory>
#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "Card.h"
#include "PokerHand.h"
#include "Deck.h"

using namespace std;

/**
 * \class PokerGame
 * \ingroup PokerGame
 *
 * \brief Logic and data structures for a poker game
 *
 * \author Josh Palmer
 */

class PokerGame {
public:
    PokerGame(int numPlayers, int numHumanPlayers);
    virtual ~PokerGame();
    void playGame();
    /// Used to sort players by hand strength
    bool operator()(Player* const &a, Player* const &b);

private:
    /// Returns the number of players left in the game
    unsigned int numberOfPlayersLeft();
    /// Returns the number of players left in the round
    unsigned int numberOfPlayersInRound();
    /// Checks to see if everyone who can bet has betted
    bool hasEveryoneBetted(int currentBet);
    /// The total number of players in the game
    unsigned int numPlayers;
    /// The number of human players in the game
    unsigned int numHumanPlayers;
    /// Data structure for players. Using pointers to take advantage of child class properties
    vector<Player *> players;
};

#endif /* POKERGAME_H_ */
