/**
 * \file PokerHand.h
 * \author Josh Palmer
 * \date October 1st, 2016
 */

#ifndef POKERHAND_H_
#define POKERHAND_H_

#include "Card.h"
#include <vector>
#include <map>

/**
 * \class PokerHand
 * \ingroup Poker
 *
 * \brief Contains the logic and data structures representing a
 *        a poker hand
 *
 * \author Josh Palmer
 */

namespace Poker_Hand_Type {
typedef enum {
    HIGH_CARD = 0,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH,
    FIVE_OF_A_KIND,
} hand_type_t;

}

class PokerHand {
public:
    PokerHand();
    PokerHand(const std::vector<Card> &hand);
    ~PokerHand();
    PokerHand(const PokerHand& rhs);
    void initializeMap();
    PokerHand& operator=(const PokerHand& rhs);

    /// Comparison operators
    friend bool operator>(const PokerHand& player1, const PokerHand& player2) {
        bool isWinner = false;
        int i;
        int numCardsInHand = 4;
        /// Find the hand that's the winner. Highest card if each hand is the same
        if (player1.getHandType() == player2.getHandType()) {
            for (i = numCardsInHand; i >= 0 ; i--) {
                if (player1.hand[i].getValue()
                        != player2.hand[i].getValue()) {
                    if (player1.hand[i].getValue()
                            > player2.hand[i].getValue()) {
                        isWinner = true;
                    } else {
                        isWinner = false;
                    }
                }
            }
        } else {
            if (player1.getHandType() > player2.getHandType()) {
                isWinner = true;
            } else {
                isWinner = false;
            }
        }
        return isWinner;
    }
    friend bool operator<(const PokerHand& player1, const PokerHand& player2) {
        bool isWinner = false;
        int i;
        int numCardsInHand = 4;
        /// Find the hand that's the winner. Highest card if each hand is the same
        if (player1.getHandType() == player2.getHandType()) {
            for (i = numCardsInHand; i >= 0; i--) {
                if (player1.hand[i].getValue()
                        != player2.hand[i].getValue()) {
                    if (player1.hand[i].getValue()
                            > player2.hand[i].getValue()) {
                        isWinner = false;
                    } else {
                        isWinner = true;
                    }
                }
            }
        } else {
            if (player1.getHandType() > player2.getHandType()) {
                isWinner = false;
            } else {
                isWinner = true;
            }
        }
        return isWinner;
    }

    friend bool operator==(const PokerHand& player1, const PokerHand& player2) {
        return ~(player1 < player2) == ~(player1 > player2);
    }

    /// The output
    friend inline ostream& operator<<(ostream& os, const PokerHand& b) {
        unsigned int i;
        for (i = 0; i < b.hand.size(); i++) {
            os << b.hand[i] << " ";
        }
        return os;
    }

    /// Used to sort cards in numerical order
    bool operator()(const Card &a, const Card &b);

    /// Returns the hand we're holding
    Poker_Hand_Type::hand_type_t getHandType() const;

    /// Returns a specific card in a hand
    int getCard(int card);

    /// Returns the entire hand
    std::vector<Card> getCards() const;

private:
    /// Numerical values for royal cards
    static const int ACE = 14;
    static const int KING = 13;
    static const int QUEEN = 12;
    static const int JACK = 11;

    /// Maps a card to its numerical value
    std::map<char, int> cardValueToInt;
    std::vector<Card> hand;
    Poker_Hand_Type::hand_type_t handType;

    /**
     * \brief Calulates the highest hand type that's being held
     *
     * This function is run at initialization
     */
    void calculateHand();

    /// Look up a card's face value
    int getCardValue(const Card &card);
};

#endif /* POKERHAND_H_ */
