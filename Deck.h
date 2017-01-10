/*
 * \file Deck.h
 * \date Nov 15, 2016
 * \author Josh Palmer
 */

#ifndef DECK_H_
#define DECK_H_

#include "Card.h"
#include <vector>
#include <deque>

using namespace std;

/**
 * \class Deck
 * \ingroup PokerGame
 *
 * \brief Logic and data structures for a deck of cards
 *
 * \author Josh Palmer
 */


class Deck {
public:
    Deck();
    Deck(Deck& rhs);
    ~Deck();
    Deck& operator=(Deck& rhs);
    /// Shuffles the deck
    void shuffle();
    /// Returns the top card. Exception raised if no card available
    Card getTopCard();
    /// Resets the deck to include all cards
    void resetDeck();
    /// Returns whether the deck is empty
    bool isDeckEmpty();
    /// Returns the number of cards in the deck
    int numCardsRemaining();

private:
    const static int NUM_SUITES = 4;
    const char suites[4] = { 'c', 's', 'd', 'h' };
    /// char array of the possible values
    vector<char> values;
    /// queue representing the deck
    deque<Card> deck;

};

#endif /* DECK_H_ */
