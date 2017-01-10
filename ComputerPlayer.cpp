/*
 * \file ComputerPlayer.cpp
 * \date Dec 1, 2016
 * \author Josh Palmer
 */

#include <random>

#include "ComputerPlayer.h"
#include "PokerHand.h"

ComputerPlayer::ComputerPlayer(int playerNum) :
        Player(playerNum) {

}

ComputerPlayer::~ComputerPlayer() {

}

ComputerPlayer::ComputerPlayer(const ComputerPlayer &rhs) :
        Player(rhs) {

}

ComputerPlayer& ComputerPlayer::operator =(const ComputerPlayer &rhs) {
    Player::operator =(rhs);
    return *this;
}
/// Logic for a betting round. Returns amount placed into pot
int ComputerPlayer::bettingRound(int currentHighBet, int pot) {
    Poker_Hand_Type::hand_type_t hand = Player::getHand().getHandType();
    int bet;
    /// See what type of hand we have, and bet accordingly
    if (hand > Poker_Hand_Type::FULL_HOUSE) {
        /// bet high
        bet = Player::getCurrentMoney();
    } else if (hand > Poker_Hand_Type::THREE_OF_A_KIND) {
        if (currentHighBet < 50) {
            bet = 50 + currentHighBet;
        } else {
            bet = currentHighBet;
        }
    }

    else if (hand >= Poker_Hand_Type::ONE_PAIR) {
        if (currentHighBet > 50) {
            bet = 0;
            cout << "Computer player #" << Player::getPlayerNumber()
                    << " has folded" << endl;
            Player::fold();
        } else if (currentHighBet < 50) {
            bet = currentHighBet + 20;
        } else {
            bet = currentHighBet;
        }
    } else {
        if (currentHighBet < 10) {
            bet = currentHighBet;
        }
        /// Just fold
        else {
            bet = 0;
            cout << "Computer player #" << Player::getPlayerNumber()
                    << " has folded" << endl;
            Player::fold();
        }
    }

    /// Have a 25% chance to bluff
    if ((rand() % 3) == 1 && !Player::hasFolded()
            && hand < Poker_Hand_Type::TWO_PAIR) {
        bet += rand() % Player::getCurrentMoney();
    }

    if (bet > Player::getCurrentMoney()) {
        bet = Player::getCurrentMoney();
    }

    Player::setCurrentBet(bet);
    Player::setCurrentMoney(Player::getCurrentMoney() - bet);
    if (bet > 0) {
        cout << "Computer player #" << Player::getPlayerNumber() << " has bet $"
                << bet << endl;
    }
    return bet;
}

/// Logic for exchanging cards
void ComputerPlayer::cardExchangeRound(Deck& deck) {
    /// Have very simple logic for card exchanging
    Poker_Hand_Type::hand_type_t handType = Player::getHand().getHandType();
    vector<Card> hand = Player::getHand().getCards();
    int i;
    if (handType < Poker_Hand_Type::ONE_PAIR) {
        int numCardsToReplace = rand() % 4;
        for (i = 0; i < numCardsToReplace; i++) {
            if (!deck.isDeckEmpty()) {
                hand.erase(hand.begin() + i);
                hand.insert(hand.begin() + i, deck.getTopCard());
            }
        }
    }
    Player::setHand(PokerHand(hand));
}
