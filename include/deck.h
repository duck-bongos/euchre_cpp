#include <algorithm>
#include <array>
#include "card.h"
#include <iostream>
#include <queue>
#include <random>
#include "suit.h"
#include <vector>

class Deck
{
public:
    // declare a vector with all 24 cards
    array<Card, 24> cards;
    array<Card, 3> three;
    array<Card, 2> two;
    queue<Card> deck;
    // constructor

    Deck()
    {
        int idx;
        int i = 0;
        int j = 0;
        for (const auto &c : {"nine", "ten", "jack", "queen", "king", "ace"})
        {
            for (const auto &s : {"hearts", "clubs", "spades", "diamonds"})
            {
                Card card = Card(c, s);
                idx = i * j + j;
                cards[idx] = card;
                j++;
            }
            i++;
        }

        // shuffle them in preparation for a deal
        shuffle();

        // reverse the order
        reverse();

        // put into queue
        putCardsInDeck();
        
    };

    void shuffle()
    {
        auto rng = std::default_random_engine{};
        std::shuffle(std::begin(cards), end(cards), rng);
    }

    void reverse() {
        std::reverse(begin(cards), end(cards));
    }

    void putCardsInDeck() {
        for (int i = 0; i < cards.size(); i++) {
            deck.push(cards[i]);
        }
    }

    array<Card, 3> dealThree() {
        for (int i = 0; i < 3; i++) {
            three[i] = deck.back();
        }
        return three;
    };

    array<Card, 2> dealTwo() {
        for (int i = 0; i < 2; i++) {
            two[i] = deck.back();
        }
        return two;
    };

    array<Card, 24> printAll() {
        for (int i = 0; i < 24; i++) {
            Card c = deck.back();
            std::cout << c.suit << " " << c.valueName << endl;
        }
        return cards;
    };



    // destructor
    ~Deck();
};
