/*
 * \file HumanPlayer.h
 * \date Nov 15, 2016
 * \author Josh Palmer
 */

#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_

#include "Player.h"

/**
 * \class PokerHand
 * \ingroup Poker
 *
 * \brief Logic for a human poker player
 *
 * \author Josh Palmer
 */

class HumanPlayer: public Player {
public:
    HumanPlayer(int playerNum);
    ~HumanPlayer();
    HumanPlayer(HumanPlayer& rhs);
    HumanPlayer& operator= (HumanPlayer& rhs);

    /// Logic for a betting round. Returns amount placed into pot
    int bettingRound(int currentHighBet, int pot);
    /// Logic for exchanging cards
    void cardExchangeRound(Deck& deck);
};

#endif /* HUMANPLAYER_H_ */
