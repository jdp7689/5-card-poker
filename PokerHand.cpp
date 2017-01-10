/*
 * \file PokerHand.cpp
 * \date October 1st, 2016
 * \author Josh Palmer
 */

#include "PokerHand.h"
#include "Card.h"
#include <vector>
#include <ctype.h>
#include <algorithm>
#include <iostream>

using namespace std;

PokerHand::PokerHand() :
        handType(Poker_Hand_Type::HIGH_CARD) {
    initializeMap();
}

PokerHand::PokerHand(const std::vector<Card> &hand) :
        hand(hand), handType(Poker_Hand_Type::HIGH_CARD) {
    initializeMap();
    if (hand.size() != 5) {
        throw "Error! invalid sized hand";
    }
    calculateHand();
}

PokerHand::~PokerHand() {

}

PokerHand::PokerHand(const PokerHand& rhs) {
    this->handType = rhs.handType;
    this->hand = rhs.hand;
    initializeMap();
}

PokerHand& PokerHand::operator=(const PokerHand& rhs) {
    this->hand = rhs.hand;
    this->handType = rhs.handType;
    initializeMap();
    return *this;
}

/// initialize map
void PokerHand::initializeMap() {
    int i;
    /// Initialize the map
    for (i = 2; i < 10; i++) {
        cardValueToInt['0' + i] = i;
    }
    // Call character '0' = 10
    cardValueToInt['0'] = 10;
    cardValueToInt['J'] = JACK;
    cardValueToInt['Q'] = QUEEN;
    cardValueToInt['K'] = KING;
    cardValueToInt['A'] = ACE;
}

/// Look up a card's face value
int PokerHand::getCardValue(const Card &card) {
    return cardValueToInt[toupper(card.getValue())];
}

/// Used to sort cards in numerical order
bool PokerHand::operator()(const Card &a, const Card &b) {
    /// Using information from http://stackoverflow.com/questions/1902311/problem-sorting-using-member-function-as-comparator
    /// Doing this lets us sort in descending order
    return getCardValue(a) < getCardValue(b);
}

/**
 * \brief Calulates the highest hand type that's being held
 *
 * This function is run at initialization
 */
void PokerHand::calculateHand() {
    int i;
    bool isFlush = false;
    bool isStraight = false;

    bool hasThreeOfAKind = false;
    int numPairs = 0;
    int value = 0;
    // First, sort the hand by descending value
    sort(hand.begin(), hand.end(), *this);

    // Lets look for hands that don't require pairs

    // Start with looking for a flush
    if (this->hand[0].getSuite() == this->hand[1].getSuite()
            && this->hand[1].getSuite() == this->hand[2].getSuite()
            && this->hand[2].getSuite() == this->hand[3].getSuite()
            && this->hand[3].getSuite() == this->hand[4].getSuite()) {
        isFlush = true;
    }

    // Do we have a straight?

    // Check for the special case first when there is an ace that can count as 14 or 1
    if (getCardValue(this->hand[4]) == ACE) {
        if (getCardValue(this->hand[0]) == 2
                && getCardValue(this->hand[1])
                        == (getCardValue(this->hand[0]) + 1)
                && getCardValue(this->hand[2])
                        == (getCardValue(this->hand[1]) + 1)
                && getCardValue(this->hand[3])
                        == (getCardValue(this->hand[2]) + 1)) {
            isStraight = true;
        }
    }
    if (getCardValue(this->hand[1]) == (getCardValue(this->hand[0]) + 1)
            && getCardValue(this->hand[2]) == (getCardValue(this->hand[1]) + 1)
            && getCardValue(this->hand[3]) == (getCardValue(this->hand[2]) + 1)
            && getCardValue(this->hand[4])
                    == (getCardValue(this->hand[3]) + 1)) {
        isStraight = true;
    }

    if (isStraight && isFlush) {
        this->handType = Poker_Hand_Type::STRAIGHT_FLUSH;
        return;
    } else if (isStraight) {
        this->handType = Poker_Hand_Type::STRAIGHT;
        return;
    } else if (isFlush) {
        this->handType = Poker_Hand_Type::FLUSH;
        return;
    }

    // How about the mystical five of a kind?
    value = getCardValue(this->hand[0]);
    if (getCardValue(this->hand[1]) == value
            && getCardValue(this->hand[2]) == value
            && getCardValue(this->hand[3]) == value
            && getCardValue(this->hand[4]) == value) {
        this->handType = Poker_Hand_Type::FIVE_OF_A_KIND;
        return;
    }

    // Check for four of a kind, now
    for (i = 0; i < 2; i++) {
        value = getCardValue(this->hand[i]);
        if (getCardValue(this->hand[i + 1]) == value
                && getCardValue(this->hand[i + 2]) == value
                && getCardValue(this->hand[i + 3]) == value) {
            this->handType = Poker_Hand_Type::FOUR_OF_A_KIND;
            return;
        }
    }

    // Moving right along, do we have three of a kind?
    for (i = 0; i < 3; i++) {
        value = getCardValue(this->hand[i]);
        if (getCardValue(this->hand[i + 1]) == value
                && getCardValue(this->hand[i + 2]) == value) {
            hasThreeOfAKind = true;
            break;
        }
    }

    // If there are three of a kind, how about a full house?
    if (hasThreeOfAKind) {
        if (i == 0) {
            if (getCardValue(this->hand[3]) == getCardValue(this->hand[4])) {
                this->handType = Poker_Hand_Type::FULL_HOUSE;
                return;
            }
        } else if (i == 2) {
            if (getCardValue(this->hand[0]) == getCardValue(this->hand[1])) {
                this->handType = Poker_Hand_Type::FULL_HOUSE;
                return;
            }
        }
        // Just set and return if not
        this->handType = Poker_Hand_Type::THREE_OF_A_KIND;
        return;
    }

    // Down to just looking for pairs now
    for (i = 0; i < 4; i++) {
        if (getCardValue(this->hand[i]) == getCardValue(this->hand[i + 1])) {
            numPairs++;
        }
    }

    if (numPairs > 0) {
        if (numPairs == 2) {
            this->handType = Poker_Hand_Type::TWO_PAIR;
        } else {
            this->handType = Poker_Hand_Type::ONE_PAIR;
        }
        return;
    }
}

/// Returns the hand we're holding
Poker_Hand_Type::hand_type_t PokerHand::getHandType() const {
    return this->handType;
}

/// Returns the entire hand
vector<Card> PokerHand::getCards() const {
    return this->hand;
}

/// Returns a specific card in a hand
int PokerHand::getCard(int card) {
    return getCardValue(hand[card]);
}
