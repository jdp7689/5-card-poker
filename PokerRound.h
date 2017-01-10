/*
 * \file PokerHand.h
 * \date October 1st, 2016
 * \author Josh Palmer
 */

#ifndef POKERROUND_H_
#define POKERROUND_H_

#include "Card.h"
#include <vector>
#include "PokerHand.h"

namespace Poker_Winner {
typedef enum {
    TIE,
    PLAYER_1_WINS,
    PLAYER_2_WINS
} winner_t;
}

/**
 * \class PokerRound
 * \ingroup Poker
 *
 * \brief Class representing a round of poker
 *
 * \author Josh Palmer
 */
class PokerRound {
public:
    PokerRound(PokerHand player1, PokerHand player2);

    /// Returns the hand's winner
    Poker_Winner::winner_t getWinner();

private:
    PokerHand player1;
    PokerHand player2;
};

#endif /* POKERROUND_H_ */
