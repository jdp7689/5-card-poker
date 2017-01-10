/*
 * \file Player.h
 * \date Nov 15, 2016
 * \author Josh Palmer
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>

#include "PokerHand.h"
#include "Card.h"
#include "Deck.h"

using namespace std;

/**
 * \class Player
 * \ingroup PokerGame
 *
 * \brief Base class for a poker player
 *
 * \author Josh Palmer
 */

class Player {
public:
    Player(int playerNumber);

    virtual ~Player();
    Player& operator=(const Player& rhs);
    Player(const Player& rhs);

    /// Indicates a new round of poker is starting
    void startNewRound(PokerHand hand);
    /// Returns the player's hand
    PokerHand getHand();
    /// Returns the amount of money the player posses
    int getCurrentMoney();
    /// Sets the amount of money the player has
    void setCurrentMoney(int newMoney);
    /// Returns the amount of money the player has put in the pot
    int getCurrentBet();
    /// Sets the amount of money the player has placed into the pot
    void setCurrentBet(int bet);
    /// Returns whether the player has been eliminated from the game
    bool hasLost();
    /// Sets the player as "lost"
    void playerLost();
    /// Sets the player as "folding" this round
    void fold();
    /// Returns whether the player has folded or not
    bool hasFolded();
    /// Returns the player's number
    int getPlayerNumber();
    /// Reset the current bet to 0
    void resetCurrentBet();
    /// Sets the hand
    void setHand(PokerHand hand);

    /// The rounds
    /// There will be two betting rounds and one round to exchange cards
    virtual int bettingRound(int currentBet, int pot) = 0;
    /// Gives option to exchange cards
    virtual void cardExchangeRound(Deck& deck) = 0;

private:
    PokerHand hand;

    const int startMoney = 200;

    /// Start off with $200
    int currentMoney;
    /// The number of the player
    int playerNumber;
    bool folded;
    int currentBet;
    bool hasPlayerLost;

};

#endif /* PLAYER_H_ */
