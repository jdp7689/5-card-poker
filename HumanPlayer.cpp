/*
 * \file HumanPlayer.cpp
 * \date Nov 15, 2016
 * \author Josh Palmer
 */

#include "HumanPlayer.h"
#include <string>
#include <sstream>
#include <exception>
#include <climits>

HumanPlayer::HumanPlayer(int playerNum) :
        Player(playerNum) {

}

HumanPlayer::~HumanPlayer() {
}

HumanPlayer::HumanPlayer(HumanPlayer& rhs) :
        Player(rhs) {

}

HumanPlayer& HumanPlayer::operator=(HumanPlayer& rhs) {
    Player::operator =(rhs);
    return *this;
}

/// Logic for a betting round. Returns amount placed into pot
int HumanPlayer::bettingRound(int currentHighBet, int pot) {
    int bet = 0;
    int raisedBet;
    string input;
    cout << "\nHello player #" << Player::getPlayerNumber() << endl;
    cout << "The current bet is $" << currentHighBet << endl;
    cout << "You currently have $" << Player::getCurrentMoney()
            << " and there is $" << pot << " in the pot" << endl;
    cout << "You have already bet this round $" << Player::getCurrentBet()
            << endl;
    cout << "Your hand:" << endl;
    cout << Player::getHand() << endl;

    if (Player::getCurrentMoney() == 0) {
        cout << "You don't have any money left. "
                << "You'll have to wait this one out" << endl;
        return bet;
    }
    bool goodResponse = false;
    do {
        cout << "Your options are: Fold(f), Raise(r), Match bet(m)" << endl;
        getline(cin, input);
        if (input.compare("f") || input.compare("r") || !input.compare("m")) {
            goodResponse = true;
        }
    } while (!goodResponse);

    if (!input.compare("f")) {
        Player::fold();
    } else if (!input.compare("m")) {
        if ((currentHighBet - Player::getCurrentBet())
                > Player::getCurrentMoney()) {
            cout << "Don't have enough money to match. Going all in!" << endl;
            bet = Player::getCurrentMoney();
        } else {
            bet = currentHighBet - Player::getCurrentBet();
        }
        Player::setCurrentBet(currentHighBet);
        Player::setCurrentMoney(Player::getCurrentMoney() - bet);
    } else if (!input.compare("r")) {
        if (Player::getCurrentMoney() < currentHighBet) {
            cout << "You don't have enough money to bet more. "
                    << "Going all in with what you've got!" << endl;
            bet = Player::getCurrentMoney();
        } else {
            cout << "How much would you like to raise the bet?" << endl;
            getline(cin, input);
            raisedBet = atoi(input.c_str());
            bet = raisedBet + currentHighBet - Player::getCurrentBet();
            if (bet > Player::getCurrentMoney()) {
                cout << "You don't have enough money!"
                        << "Going all in with what you've got" << endl;
                bet = Player::getCurrentMoney();
            }
        }
        Player::setCurrentBet(bet);
        Player::setCurrentMoney(Player::getCurrentMoney() - bet);
    }

    return bet;
}

/// Logic for exchanging cards
void HumanPlayer::cardExchangeRound(Deck& deck) {
    string input;
    string replaceCard;
    vector<Card> hand;
    int numCardsReplacing = 0;

    cout << "\nPlayer " << Player::getPlayerNumber() << endl;
    cout << "Your cards, numbered 0 - 4:" << endl;
    cout << Player::getHand() << endl;
    cout << "Enter each card to replace with a "
            << "space between each number to replace" << endl;

    getline(cin, input);
    stringstream strstr(input);
    hand = Player::getHand().getCards();

    while (getline(strstr, replaceCard, ' ')) {
        if (deck.numCardsRemaining() == numCardsReplacing) {
            cout << "Nothing left in the deck" << endl;
            break;
        }
        numCardsReplacing++;
        if (atoi(replaceCard.c_str()) > 4) {
            throw "Gave incorrect number for card replacing!";
        }
        hand.erase(hand.begin() + atoi(replaceCard.c_str()));
        hand.insert(hand.begin() + atoi(replaceCard.c_str()),
                deck.getTopCard());
    }
    Player::setHand(PokerHand(hand));
    cout << "Your new hand" << endl;
    cout << Player::getHand() << "\n" << endl;

}

