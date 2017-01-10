/*
 * \file Deck.cpp
 * \date Nov 15, 2016
 * \author Josh Palmer
 */

#include "Deck.h"
#include <cstdlib>

Deck::Deck() {
    /// Create new deck
    int i;
    /// Initialize applicable card values
    values.reserve(13);
    for (i = 0; i < 8; i++) {
        values.push_back('0' + i + 2);
    }
    values.push_back('0');
    values.push_back('J');
    values.push_back('Q');
    values.push_back('K');
    values.push_back('A');

    resetDeck();
    shuffle();
}

Deck::~Deck() {
}

Deck::Deck(Deck& rhs) {
    this->deck = rhs.deck;
}

Deck& Deck::operator=(Deck& rhs) {
    this->deck = rhs.deck;
    return *this;
}
/// Returns whether the deck is empty
bool Deck::isDeckEmpty() {
    return 0 == deck.size();
}
/// Returns the number of cards in the deck
int Deck::numCardsRemaining() {
    return deck.size();
}

/// Shuffles the deck
void Deck::shuffle() {
    /// Based off of Fisher-Yates
    int i;
    srand(time(NULL));
    for (i = deck.size(); i > 0; i--) {
        /// Get random value between 0 and i
        int randomValue = rand() % i;

        /// exchange deck[j] and deck[i]
        Card tempCard = deck[i];
        deck[i] = deck[randomValue];
        deck[randomValue] = tempCard;
    }
}
/// Resets the deck to include all cards
void Deck::resetDeck() {
    unsigned int i, j;
    /// Set up a new deck
    deck.clear();

    for (i = 0; i < NUM_SUITES; i++) {
        for (j = 0; j < this->values.size(); j++) {
            Card card(this->suites[i], this->values[j]);
            deck.push_back(card);
        }
    }
}
/// Returns the top card. Exception raised if no card available
Card Deck::getTopCard() {
    /// Returns top card on the deck
    Card tempCard = deck.front();
    deck.pop_front();

    return tempCard;
}
