/*
 * \file Player.cpp
 * \date Nov 15, 2016
 * \author Josh Palmer
 */

#include "Player.h"

Player::Player(int playerNumber) :
        currentMoney(startMoney), playerNumber(playerNumber), folded(false), hasPlayerLost(
                false), currentBet(0) {
}

Player::Player(const Player& rhs) :
        hand(rhs.hand), currentMoney(rhs.currentMoney), playerNumber(
                rhs.playerNumber), folded(rhs.folded), hasPlayerLost(
                rhs.hasPlayerLost), currentBet(0) {

}

Player& Player::operator=(const Player& rhs) {
    this->hand = rhs.hand;
    this->currentMoney = rhs.currentMoney;
    this->currentBet = rhs.currentBet;
    this->playerNumber = rhs.playerNumber;
    this->folded = rhs.folded;
    this->hasPlayerLost = rhs.hasPlayerLost;
    return *this;
}

/// Sets the amount of money the player has placed into the pot
void Player::setCurrentBet(int bet) {
    this->currentBet = bet;
}
/// Returns the amount of money the player posses
int Player::getCurrentMoney() {
    return this->currentMoney;
}
/// Sets the amount of money the player has
void Player::setCurrentMoney(int newMoney) {
    this->currentMoney = newMoney;
}

Player::~Player() {
}
/// Returns the player's number
int Player::getPlayerNumber() {
    return this->playerNumber;
}
/// Indicates a new round of poker is starting
void Player::startNewRound(PokerHand hand) {
    this->hand = hand;
    this->currentBet = 0;
    this->folded = false;
}
/// Sets the player as "lost"
void Player::playerLost() {
    this->hasPlayerLost = true;
}
/// Returns the amount of money the player has put in the pot
int Player::getCurrentBet() {
    return this->currentBet;
}
/// Returns whether the player has been eliminated from the game
bool Player::hasLost() {
    return this->hasPlayerLost;
}
/// Returns the player's hand
PokerHand Player::getHand() {
    return this->hand;
}
/// Sets the player as "folding" this round
void Player::fold() {
    this->folded = true;
}
/// Returns whether the player has folded or not
bool Player::hasFolded() {
    return this->folded;
}
/// Reset the current bet to 0
void Player::resetCurrentBet() {
    this->currentBet = 0;
}
/// Sets the hand
void Player::setHand(PokerHand hand) {
    this->hand = hand;
}
