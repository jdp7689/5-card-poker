/*
 * \file Card.cpp
 * \date October 1st, 2016
 * \author Josh Palmer
 */

#include "Card.h"

Card::Card(char suite, char value) :
        value(value), suite(suite) {
}


Card::Card(const Card& rhs) :
        value(rhs.value), suite(rhs.suite) {
}

Card& Card::operator=(const Card& rhs) {
    this->suite = rhs.suite;
    this->value = rhs.value;
    return *this;
}

/// Reset the card value
void Card::setCard(char& suite, char& value) {
    this->suite = suite;
    this->value = value;
}

/// Return the card's value
char Card::getValue() const {
    return value;
}

/// Return the card's suite
char Card::getSuite() const {
    return suite;
}
