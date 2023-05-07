#include <algorithm>
#include <array>
#include <iostream>
#include <queue>
#include <random>
#include <vector>
#include <stdio.h>
#include <string>
#include "card.h"
#include "player.h"

class Deck
{
public:
    // declare a vector with all 24 cards
    array<Card, 24> cards;
    array<Card*, 3> three;
    array<Card*, 2> two;

    // An index will let us treat this as a queue
    int idx = 0; 

    // constructor
    Deck()
    {
        int idx_ = 0;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 9; j < 15; j++)
            {
                Card c = Card(i, j);
                // add to the list of cards
                this->cards[idx_] = c;
                idx_++;
            }
        }

        // shuffle them in preparation for a deal
        int r = rand()  % 1000;
        shuffle(r);

        // reverse the order
        reverse();

    };

    void shuffle(int randNumber)
    {
        auto rng = std::default_random_engine(randNumber);
        std::shuffle(std::begin(cards), end(cards), rng);
    }

    void reverse()
    {
        std::reverse(begin(cards), end(cards));
    }

    array<Card*, 3> dealThree()
    {
        for (int i = 0; i < 3; i++)
        {
            // cout << &cards[idx + i] << endl;
            three[i] = &cards[idx];
            // remove from deck
            // cards[idx + 1] = Card();
            idx += 1;
        }
        return three;
    };

    array<Card*, 2> dealTwo()
    {
        for (int i = 0; i < 2; i++)
        {
            two[i] = &cards[idx];
            // remove from deck
            // cards[idx + 1] = Card();
            idx += 1;
        }
        return two;
    };

    int pickDealer() {
        bool jack_found = false;
        int idx_ = 0;
        int dealer = -1;
        while (!jack_found) {
            Card* card = &cards[idx_];
            if (card->value == 11) {
                jack_found = true;
                dealer = idx_ % 4;
            }
            idx_++;
        }
        return dealer;
    }

    Card * dealCards(
        int dealerId, 
        Player * one, 
        Player * two, 
        Player * three, 
        Player * four
    ) {
        // Assumption - players: one, two, three, and four 
        // are sitting in clockwise order.
        Player* order[4] = {one, two, three, four};
        for (int i = 0; i < 8; i++) {
            int playerId = (dealerId + i) % 4;
            // cout << "Player ID: " << playerId;
            // cout << " | Iterator ID: " << i;
            // cout << " | IDX: " << idx << endl;
            // cout << "Player ID Address: " << &order[playerId] << endl;
            
            if (i < 4 && i % 2 == 0) {
                array<Card*, 3> t = dealThree();
                // cout << "Card ID" << t[0] << endl;
                order[playerId]->addCards(t);
            }
            else if (i < 4 && i % 2 == 1) {
                array<Card*, 2> t = dealTwo();
                // cout << "Card ID" << t[0] << endl;
                order[playerId]->addCards(t);
            }
            else if (i >= 4 && i % 2 == 0) {
                array<Card*, 2> t = dealTwo();
                // cout << "Card ID" << t[0] << endl;
                order[playerId]->addCards(t);
            }
            else {
                array<Card*, 3> t = dealThree();
                // cout << "Card ID" << t[0] << endl;
                order[playerId]->addCards(t);
            }
        }
        return &cards[idx+1];
    }

    void printAll()
    {
        for (int i = 0; i < 24; i++)
        {
            std::cout << i << " " << cards[i].value << " of " << cards[i].suit << "\n";
        }
    };

    // destructor
    ~Deck(){};

private:
    string values[6] = {"nine", "ten", "jack", "queen", "king", "ace"};
    size_t vsize = sizeof(values) / sizeof(values[0]);

    string suits[4] = {"hearts", "clubs", "spades", "diamonds"};
    size_t ssize = sizeof(suits) / sizeof(values[0]);
};
