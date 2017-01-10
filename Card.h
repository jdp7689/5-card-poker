/*
 * \file Card.h
 * \date October 1st, 2016
 * \author Josh Palmer
 */

#ifndef CARD_H_
#define CARD_H_
/**
 * \class Card
 * \ingroup Poker
 *
 * \brief Class representing a single card
 *
 * \author Josh Palmer
 */
#include <iostream>
#include <string>

using namespace std;

class Card {
public:
    Card(char suite, char value);
    Card& operator=(const Card& rhs);
    Card(const Card& rhs);

    inline friend ostream& operator<< (ostream& os, const Card& b) {
        os << string(1, b.suite);
        if (b.value == '0') {
            os << "10";
        }
        else {
            os << string(1, b.value);
        }
        return os;
    }

    /// Set the card value
    void setCard(char& suite, char& value);

    /// Return the card's suite
    char getSuite() const;

    /// Return the card's value
    char getValue() const;

private:
    char value;
    char suite;
};

#endif /* CARD_H_ */
