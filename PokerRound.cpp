/*
 * \file PokerRound.cpp
 * \author Josh Palmer
 * \date October 1st, 2016
 */

#include <vector>
#include <iostream>
#include "PokerRound.h"
#include "PokerHand.h"
#include "Card.h"

using namespace std;

PokerRound::PokerRound(PokerHand player1, PokerHand player2) :
        player1(player1), player2(player2) {
}

/// Returns the hand's winner
Poker_Winner::winner_t PokerRound::getWinner() {
    Poker_Winner::winner_t winner = Poker_Winner::TIE;
    unsigned int i;

    /// Find the hand that's the winner. Highest card if each hand is the same
    if (this->player1.getHandType() == this->player2.getHandType()) {
        for (i = 0; i < player1.getCards().size(); i++) {
            if (this->player1.getCard(i) != this->player2.getCard(i)) {
                if (this->player1.getCard(i) > this->player2.getCard(i)) {
                    winner = Poker_Winner::PLAYER_1_WINS;
                } else {
                    winner = Poker_Winner::PLAYER_2_WINS;
                }
            }
        }
    } else {
        if (this->player1.getHandType() > this->player2.getHandType()) {
            winner = Poker_Winner::PLAYER_1_WINS;
        } else {
            winner = Poker_Winner::PLAYER_2_WINS;
        }
    }
    return winner;
}
