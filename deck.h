#include <algorithm>
#include "card.h"
#include <random>
#include "suit.h"
#include <vector>

class Deck
{
public:
    // declare a vector with all 24 cards
    vector<Card> deck[24];

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
                deck->push_back(card);
                j++;
            }
            i++;
        }
    };

    void shuffle()
    {
        auto rng = std::default_random_engine{};
        std::shuffle(std::begin(deck), end(deck), rng);
    }

    // destructor
    ~Deck();
};
