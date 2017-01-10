/*
 * \file PokerGame.cpp
 * \date Nov 15, 2016
 * \author Josh Palmer
 */

#include "PokerGame.h"

PokerGame::PokerGame(int numPlayers, int numHumanPlayers) :
        numPlayers(numPlayers), numHumanPlayers(numHumanPlayers) {

}

PokerGame::~PokerGame() {
}

bool PokerGame::operator()(Player* const &a, Player* const &b) {
    return a->getHand() > b->getHand();
}

/// This class contains the logic and instructions for playing a poker game
void PokerGame::playGame() {
    unsigned int i;
    unsigned int j;
    unsigned int pot;
    unsigned int numCardsInHand = 5;
    /// Player who starts the round
    int antePlayer = 0;

    int currentHighBet;

    /// First step is to make all the players' objects
    for (i = 0; i < this->numHumanPlayers; i++) {
        this->players.push_back(new HumanPlayer(i));
    }
    for (; i < this->numPlayers; i++) {
        this->players.push_back(new ComputerPlayer(i));
    }

    /// Play game until one one player still has money
    while (numberOfPlayersLeft() > 1) {
        /// Initialize pot and current bet to 0
        pot = 0;
        currentHighBet = 0;
        /// Create a new deck for each game
        Deck deck;
        /// Create vectors with 5 cards each (the hands)
        vector<vector<Card> > hands(5, vector<Card>());
        for (i = 0; i < numCardsInHand; i++) {
            for (j = 0; j < numberOfPlayersLeft(); j++) {
                hands[j].push_back(deck.getTopCard());
            }
        }

        /// Give hands to each players
        j = 0;
        for (i = 0; i < this->players.size(); i++) {
            if (!this->players[i]->hasLost()) {

                this->players[i]->startNewRound(PokerHand(hands[j]));
                j++;
            }
        }

        /// Start the first betting round. Every player gets to participate (if they're still in the game)!
        /// Person who is the ante player goes first
        for (i = 0; i < this->players.size(); i++) {
            int currentPlayer = (i + antePlayer) % this->players.size();
            if (!this->players[currentPlayer]->hasLost()) {
                int playerBet = this->players[currentPlayer]->bettingRound(
                        currentHighBet, pot);
                pot += playerBet;
                if (playerBet > currentHighBet) {
                    currentHighBet = playerBet;
                }
            }
        }

        /// If money has been betted, let everyone who has not folded continue betting until
        /// everyone has bet the same amount into the pot (or has placed all their money into the pot)
        while (!hasEveryoneBetted(currentHighBet)) {
            for (i = 0; i < this->players.size(); i++) {
                int currentPlayer = (i + antePlayer) % this->players.size();
                if (!this->players[currentPlayer]->hasFolded()
                        && this->players[currentPlayer]->getCurrentBet()
                                < currentHighBet
                        && players[currentPlayer]->getCurrentMoney()) {
                    int playerBet = this->players[currentPlayer]->bettingRound(
                            currentHighBet, pot);
                    pot += playerBet;
                    if (playerBet > currentHighBet) {
                        currentHighBet = playerBet;
                    }
                }
            }
        }
        /// Continue if there are still people in the round
        if (numberOfPlayersInRound() > 1) {
            /// Card exchange time! Give the deck to each player
            /// and let them decide how many cards to discard
            for (i = 0; i < this->players.size(); i++) {
                int currentPlayer = (i + antePlayer) % this->players.size();
                if (!this->players[currentPlayer]->hasFolded()
                        && !this->players[currentPlayer]->hasLost()) {
                    this->players[currentPlayer]->cardExchangeRound(deck);
                }
            }

            /// Do another betting round as before,
            /// but only players who have not folded get to participate
            for (i = 0; i < this->players.size(); i++) {
                int currentPlayer = (i + antePlayer) % this->players.size();
                if (!this->players[currentPlayer]->hasFolded()
                        && !this->players[currentPlayer]->hasLost()) {
                    this->players[currentPlayer]->resetCurrentBet();
                }
            }

            currentHighBet = 0;
            /// People who have already folded don't get here
            for (i = 0; i < this->players.size(); i++) {
                int currentPlayer = (i + antePlayer) % this->players.size();
                if (!this->players[currentPlayer]->hasLost()
                        && !this->players[currentPlayer]->hasFolded()
                        && this->players[currentPlayer]->getCurrentMoney()) {
                    int playerBet = this->players[currentPlayer]->bettingRound(
                            currentHighBet, pot);
                    pot += playerBet;
                    if (playerBet > currentHighBet) {
                        currentHighBet = playerBet;
                    }
                }
            }
        }
        /// If money has been betted, let everyone who has not folded continue betting until
        /// everyone has bet the same amount into the pot (or has placed all their money into the pot)
        while (!hasEveryoneBetted(currentHighBet)) {
            for (i = 0; i < this->players.size(); i++) {
                int currentPlayer = (i + antePlayer) % this->players.size();
                if (!this->players[currentPlayer]->hasFolded()
                        && this->players[currentPlayer]->getCurrentBet()
                                < currentHighBet
                        && players[currentPlayer]->getCurrentMoney() != 0) {
                    int playerBet = this->players[currentPlayer]->bettingRound(
                            currentHighBet, pot);
                    pot += playerBet;
                    if (this->players[currentPlayer]->getCurrentBet()
                            > currentHighBet) {
                        currentHighBet =
                                this->players[currentPlayer]->getCurrentBet();
                    }
                }
            }
        }

        /// Find the winner and award them the pot. If there is a tie, divy up the pot accordingly
        vector<Player *> temp;
        for (i = 0; i < this->players.size(); i++) {
            if (!this->players[i]->hasFolded()
                    && !this->players[i]->hasLost()) {
                temp.push_back(this->players[i]);
            }
        }
        /// sort them all. Top one takes all
        sort(temp.begin(), temp.end(), *this);

        if (temp.size() == 1) {
            cout << "\nPlayer " << temp[0]->getPlayerNumber() << " has won $"
                    << pot << " with a hand of: " << endl;
            cout << temp[0]->getHand() << "\n" << endl;
            temp[0]->setCurrentMoney(temp[0]->getCurrentMoney() + pot);
        } else if (temp.size() == 0) {
            cout << "Everyone decided to fold? Bummer." << endl;
        } else {
            /// First case is for no tie
            if (temp[0]->getHand() > temp[1]->getHand()) {
                cout << "\nPlayer " << temp[0]->getPlayerNumber()
                        << " has won $" << pot << " with a hand of: " << endl;
                cout << temp[0]->getHand() << "\n" << endl;
                temp[0]->setCurrentMoney(temp[0]->getCurrentMoney() + pot);
            } else {
                /// Find how many people have tied
                for (i = 1;
                        i < temp.size()
                                && (temp[0]->getHand() == temp[i]->getHand());
                        i++) {

                }
                /// divy up the pot
                pot = pot / (i + 1);
                cout << "These players have tied and have won $" << pot << endl;
                for (; i >= 0; i--) {
                    temp[i]->setCurrentMoney(temp[i]->getCurrentMoney() + pot);
                    cout << temp[i]->getPlayerNumber() << endl;
                }
            }
        }

        /// Mark all the losers. They're done.
        for (i = 0; i < players.size(); i++) {
            if (!players[i]->hasLost() && players[i]->getCurrentMoney() == 0) {
                players[i]->playerLost();
                cout << "Player #" << players[i]->getPlayerNumber()
                        << " eliminated!" << endl;
            }
        }
        /// Move ante up
        antePlayer++;
        antePlayer = antePlayer % this->players.size();
    }

    /// Game over! Announce the winner + winnings and delete all objects
    for (i = 0; i < this->players.size(); i++) {
        if (!this->players[i]->hasLost()) {
            cout << "\nPlayer #" << this->players[i]->getPlayerNumber()
                    << " has won the game! Total winnings: $"
                    << this->players[i]->getCurrentMoney() << endl;
        }
    }

    for (i = 0; i < this->players.size(); i++) {
        delete this->players[i];
    }
}

/// Ensures everyone has betted at the current high bet
bool PokerGame::hasEveryoneBetted(int currentHighBet) {
    unsigned int i;
    bool allBetsIn = true;
    for (i = 0; i < this->players.size(); i++) {
        if (!this->players[i]->hasFolded() && !this->players[i]->hasLost()
                && this->players[i]->getCurrentBet() < currentHighBet && players[i]->getCurrentMoney()) {
            allBetsIn = false;
        }
    }
    return allBetsIn;
}

unsigned int PokerGame::numberOfPlayersInRound() {
    int numPlayersRemaining = 0;
    unsigned int i;
    for (i = 0; i < this->players.size(); i++) {
        if (!this->players[i]->hasFolded()) {
            numPlayersRemaining++;
        }
    }
    return numPlayersRemaining;
}

/// Checks to see how many players are left
unsigned int PokerGame::numberOfPlayersLeft() {
    int numPlayersWithMoney = 0;
    unsigned int i;
    for (i = 0; i < this->players.size(); i++) {
        if (!this->players[i]->hasLost()) {
            numPlayersWithMoney++;
        }
    }
    return numPlayersWithMoney;
}
