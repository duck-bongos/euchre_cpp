#pragma once
#include <iostream>
#include <map>
#include <string.h>

using namespace std;
// Define BSON


static const map<int, string>values{{0, "NULL"}, {9, "Nine"}, {10, "Ten"}, {11, "Jack"}, {12, "Queen"}, {13, "King"}, {14, "Ace"}};
static const map<int, string>suits{{-1, "NULL"}, {0, "Clubs"}, {1, "Diamonds"}, {2, "Spades"}, {3, "Hearts"}};


class Card
{
public:
    Card() {
        this->suit = -1;
        this->value = 0;
        this->color = -1;
    }
    Card(int suit, int value) {
        this->suit = suit;
        this-> color = suit % 2;
        this->value = value;
    };
    // 0 - clubs, 1 - diamonds, 2 - spades, 3 - hearts
    int suit = 0; 
    
    // 0 if black, 1 if red
    int color= suit % 2;

    // Off-Trump 9 - 14: 9,10,J,Q,K,A
    // Trump 15,16,17,18,19,20
    /*
               | 9  | 10 | J  | Q  | K  | A  | JL | JR | 
    ----------------------------------------------------
        Trump  | 9  | 10 | 11 | 12 | 13 | 14 | -  | -  |
    Off Trump: | 18 | 19 | -  | 21 | 22 | 23 | 24 | 25 |
    ----------------------------------------------------
    */
    int value;

    void set_trump(int trump_suit) {
        int ts = trump_suit % 2;
        // Right Bauer
        if (value == 11 && suit == trump_suit) {
            value = 25;
        }

        // Left Bauer
        else if (value == 11 && ts == color) {
            value = 24;
        }

        // Everything else
        else if (trump_suit == suit) {
            value += 9;
        }
    }

    void unset_trump() {
        if (value >= 24) {
            value = 11;
        }
        else if (value >= 18 && value < 24) {
            value -= 9;
        }
    }

    void discard() {
        this->suit = -1;
        this->value = 0;
        this->color = -1;
    }

    friend ostream &operator<< (ostream &output, const Card &C) {
        output << values.at(C.value) << " of " << suits.at(C.suit);
        return output;
    }

    ~Card(){};
};