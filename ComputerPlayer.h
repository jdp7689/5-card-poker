/*
 * \file ComputerPlayer.h
 * \date Dec 1, 2016
 * \author Josh Palmer
 */

#ifndef COMPUTERPLAYER_H_
#define COMPUTERPLAYER_H_

#include "Player.h"

/**
 * \class PokerHand
 * \ingroup Poker
 *
 * \brief Logic for a computer poker player
 *
 * \author Josh Palmer
 */

class ComputerPlayer: public Player {
public:
    ComputerPlayer(int playerNumber);
    ~ComputerPlayer();
    ComputerPlayer(const ComputerPlayer& rhs);
    ComputerPlayer& operator= (const ComputerPlayer& rhs);

    /// Logic for a betting round. Returns amount placed into pot
    int bettingRound(int currentHighBet, int pot);
    /// Logic for exchanging cards
    void cardExchangeRound(Deck& deck);
};

#endif /* COMPUTERPLAYER_H_ */
